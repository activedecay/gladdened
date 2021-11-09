# grid
make a grid using screen width and height
- want rectangular geometry in a grid with rows and columns as independent variables
- the number of rows    changes with the resize event and is a mod of the height
- the number of columns changes with the resize event and is a mod of the width
- we can draw the geometry using triangle strips and a single vertex array
  - NOTE: for every top-left, we'd have to update the UVs
  - CON: there are many top-left vertices that are repeated ... literally all over
  - RESULT: we should probably just use instances
- use element arrays of a single rectangle and use it to draw instances
  - configure the location of the vertices in the instance
    - TODO: figure out how element instances are placed there's more pseudocode here
  - for every instanceId:
    - update the uv coordinates and texture the rectangle using the glyph texture

glyph cache
- throw away the glyph cache if the user changes the font size
- pre-populate the glyph cache with the ascii character set
- hash the locations of the glyphs in the uv texture map
  - hash keys are the character value
  - hash values are uv coordinates in the texture or -1
    - if -1 we need to laugh ourselves silly because we didn't implement this yet
- the day we get to writing unicode characters will be a fucking miracle.
  - hashing character and getting -1 means we probably got a unicode character
    - compute the unicode character's texture and update the texture 
    - create an entry for the UVs it in the texture map
