#include "gladdened.h"

FT_Library library;   /* handle to library     */
FT_Face face;         /* handle to face object */

FT_Error e;

void fonts_init(int gl_texture_unit) {
  e = FT_Init_FreeType(&library);
  if (e)
    error_at_line(0, errno, __FILE__, __LINE__,
                  "lmao %d", e);

  e = FT_New_Face(library,
                  "../fonts/SourceCodePro-Regular.ttf",
                  0,
                  &face);
  //  alternatively, read a file into memory and create a new face object
  //  note? you must not deallocate the buffer before calling FT_Done_Face
  //  e = FT_New_Memory_Face(library,
  //      buffer,      /* first byte in memory */
  //      size,        /* size in bytes        */
  //      0,  /* face_index  */
  //      &face);
  // there are other ways to load a font as well, such as using sockets.
  if (e == FT_Err_Unknown_File_Format) {
    error_at_line(0, errno, __FILE__, __LINE__,
                  "unknown file format %d", e);
    //... the font file could be opened and read, but it appears
    //... that its font format is unsupported
  } else if (e) {
    error_at_line(0, errno, __FILE__, __LINE__,
                  "font file could not be opened %d", e);
    //... another e code means that the font file could not
    //... be opened or read, or that it is broken...
  }

  // https://freetype.org/freetype2/docs/reference/ft2-base_interface.html#ft_facerec
  // a comprehensive list of these descriptions is in the link above. here's a few:
  printf("num glyphs %ld\n", face->num_glyphs); /* character images, not necessarily character codes */
  printf("face flags %lx\n", face->face_flags); /* face properties: scalable, etc. */
  printf("units em %uh\n", face->units_per_EM); /* valid only for scalable */
  printf("num strikes %d\n", face->num_fixed_sizes); /* count of embedded bitmap strikes */
  if (face->available_sizes)
    printf("size w%d h%d\n", face->available_sizes->width, face->available_sizes->height);
  FT_Size size = face->size;

  e = FT_Set_Char_Size(// this sets the height using points
    face,    /* handle to face object */
    0,       /* char_width in 1/64th of points; 0 if same as height  */
    16 * 64,   /* char_height in 1/64th of points */
    300,     /* horizontal device resolution    */
    300);   /* vertical device resolution      */
  if (e)
    error_at_line(0, errno, __FILE__, __LINE__,
                  "lmao %d", e);

  e = FT_Set_Pixel_Sizes(// alternatively, to set the size to an exact pixel height
    face,   /* handle to face object */
    0,      /* pixel_width; 0 if same as height */
    16);   /* pixel_height */
  if (e)
    error_at_line(0, errno, __FILE__, __LINE__,
                  "lmao %d", e);

  FT_UInt glyph_index0 = FT_Get_Char_Index(face, 'a'); /* to load character U+1F028, use value 0x1F028 */
  printf("char index of 'a'(%d) %d\n", 'a', glyph_index0);

  FT_Int32 load_flags = FT_LOAD_RENDER; // note: see face->glyph properties after loading
  e = FT_Load_Glyph(
    face,          /* handle to face object */
    glyph_index0,   /* glyph index           */
    load_flags);  /* load flags, see below */
  if (e)
    error_at_line(0, errno, __FILE__, __LINE__,
                  "lmao %d", e);

  // glyph images are stored in glyph slot objects
  //FT_GlyphSlot g = face->glyph; // a glyph slot object

  // note I have inspected the glyph here, and noted that by default
  // the glyph slot (face->glyph) has a format of OUTLINE. changed load_flags
  // to FT_LOAD_RENDER to get a FT_GLYPH_FORMAT_BITMAP which allows us to render
  // the glyph below.

  FT_Render_Mode render_mode = FT_RENDER_MODE_NORMAL; /* set to FT_RENDER_MODE_MONO for 1-bit monochrome */
  e = FT_Render_Glyph(face->glyph,   /* glyph slot  */
                      render_mode); /* render mode */
  if (e)
    error_at_line(0, errno, __FILE__, __LINE__,
                  "lmao %d", e);

  // the documentation says to use Load_Char to do the two steps above in one
  // FT_Load_Char(face, i, FT_LOAD_RENDER)

  FT_GlyphSlot slot = face->glyph;  /* a small shortcut */
  FT_UInt glyph_index;
  // from 0x20(32)[:space:] to 0x7e(126)[~]
  char first = ' ';
  char last = '~';
  char num_chars = last - first, i;
  int max_height = 0, baseline;

  if (FT_IS_SCALABLE(face)) {
    max_height = (face->bbox.yMax >> 6) - (face->bbox.yMin >> 6);
    baseline = face->ascender >> 6; // the baseline is at 0 - ascender (if +y is pointing down)
  }

  GLubyte data[940*23] = {0};

  glTexSubImage2D(GL_TEXTURE_2D,
                  0, // mipmap level
                  0, 0,
                  940, 23, // location in texture
                  GL_RED, GL_UNSIGNED_BYTE, data); // data

  /* pixels in x,y */
  int pen_x = 0, pen_y = 0;
  for (i = first; i < first + num_chars; i++) {
    /* load glyph image into the slot (erase previous one) */
    e = FT_Load_Char(face, i, FT_LOAD_RENDER);
    if (e)
      continue;  /* ignore errors */

    /* now, draw to our target surface, maybe like this:
     * (metrics.advance.x) == slot->bitmap_left and (metrics.advance.y) == slot->bitmap_top
     * &slot->bitmap, pen_x + slot->bitmap_left, pen_y - slot->bitmap_top */
    pen_y = baseline - slot->bitmap_top;
    if (pen_y + slot->bitmap.rows >= max_height-3)
      exit(10);

    /* optimally, bitmaps should be used as an alpha channel
     * in linear blending with gamma correction {|}*/
    glTexSubImage2D(GL_TEXTURE_2D,
                        0, // mipmap level
                        pen_x + slot->bitmap_left, pen_y, // location in texture
                        slot->bitmap.width, slot->bitmap.rows, // sub-image to write
                        GL_RED, GL_UNSIGNED_BYTE, slot->bitmap.buffer); // data

    /* increment pen positionA]Z[] */
    pen_x += slot->advance.x >> 6; // `advance` has units of 1/64th of a pixel
   // slot->bitmap.width could have been used here I guess, but then we'd have to remember
   // how wide every glyph is. oh, we might have to do that someday anyway.
   // let's cheat for now. this is a problem for an older juspin!
  }
  printf("width and height %d, %d\n", pen_x, max_height);
}
