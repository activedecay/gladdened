#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wpointer-sign"

#include <stdio.h>

#define STB_TRUETYPE_IMPLEMENTATION  // force following include to generate implementation

#include "stb_truetype.h"

char ttf_buffer[1 << 25];

/* cute little program that prints an 'a' rendered as ascii art (literally from stb_truetype.h). */
int main(int argc, char **argv) {
  stbtt_fontinfo font;
  unsigned char *bitmap;
  int w, h, i, j, codepoint = (argc > 1 ? atoi(argv[1]) : 'a'), s = (argc > 2 ? atoi(argv[2]) : 20);

  fread(ttf_buffer, 1, 1 << 25,
        fopen(argc > 3 ? argv[3] : "../fonts/SourceCodePro-Regular.ttf",
              "rb"));

  stbtt_InitFont(&font, ttf_buffer, stbtt_GetFontOffsetForIndex(ttf_buffer, 0));
  int xoff = 0;
  int yoff = 0;
  bitmap = stbtt_GetCodepointBitmap(&font, 0, stbtt_ScaleForPixelHeight(&font, s),
                                    codepoint, &w, &h, &xoff, &yoff);

  for (j = 0; j < h; ++j) {
    for (i = 0; i < w; ++i)
      putchar(" .:ioVM@"[bitmap[j * w + i] >> 5]);
    putchar('\n');
  }
  return 0;
}

#pragma clang diagnostic pop