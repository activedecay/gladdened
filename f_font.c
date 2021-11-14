#include "f_font.h"

FT_Library  library;   /* handle to library     */
FT_Face     face;      /* handle to face object */

FT_Error e;

void proc() {
  e = FT_Init_FreeType(&library );
  if ( e ) {

  }

  e = FT_New_Face(library,
                  "/usr/share/fonts/truetype/dejavu/DejaVuSansMono.ttf",
                  0,
                  &face );
  if (e == FT_Err_Unknown_File_Format )
  {
    ... the font file could be opened and read, but it appears
    ... that its font format is unsupported
  }
  else if ( e )
  {
    ... another e code means that the font file could not
    ... be opened or read, or that it is broken...
  }
}