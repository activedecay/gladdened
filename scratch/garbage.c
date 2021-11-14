
/* glCreateTextures glDeleteTextures @p.260 */
enum TextureObjectIds {
  Fonts, NumTextureObjects
};
/* glCreateTextures glDeleteTextures @p.260 */
GLuint TextureObjects[NumTextureObjects];
/* glTextureStorageXD @p.261 */
enum Texture_IDs {
  FontBuffer, NumTextures
};
/* glTextureStorageXD @p.261 */
GLuint Textures[NumTextures];

/* todo an attempt was made to create a texture

  GLfloat *texture;
  int textureSize = 4096 * 8;
  int e = posix_memalign((void **) &texture, 4096, textureSize);
  if (e)
    error(1, errno, "could not alloc texture");

  glGenTextures(NumTextures, TOs);
  glBindTexture(GL_TEXTURE_BUFFER, TOs[FontBuffer]);

  glCreateTextures(NumTextures, Textures);
  glNamedBufferStorage(Textures[FontBuffer], textureSize, texture, GL_DYNAMIC_STORAGE_BIT);
*/


/* access with shader variable sampler2D @p.259 */
glCreateTextures(GL_TEXTURE_2D, NumTextureObjects, TextureObjects); // todo glDeleteTextures()
GLuint texture_name = TextureObjects[Fonts];
GLsizei mip_levels = 0;
int texture_width = 8;
int texture_height = 8;
glTextureStorage2D(texture_name, mip_levels, GL_RGBA32F, texture_width, texture_height);
GLfloat texture_checkerboard[] = {
  1.f,1.f,1.f,1.f, 0.f,0.f,0.f,1.f, 1.f,1.f,1.f,1.f, 0.f,0.f,0.f,1.f, 1.f,1.f,1.f,1.f, 0.f,0.f,0.f,1.f, 1.f,1.f,1.f,1.f, 0.f,0.f,0.f,1.f,
  1.f,1.f,1.f,1.f, 0.f,0.f,0.f,1.f, 1.f,1.f,1.f,1.f, 0.f,0.f,0.f,1.f, 1.f,1.f,1.f,1.f, 0.f,0.f,0.f,1.f, 1.f,1.f,1.f,1.f, 0.f,0.f,0.f,1.f,
  1.f,1.f,1.f,1.f, 0.f,0.f,0.f,1.f, 1.f,1.f,1.f,1.f, 0.f,0.f,0.f,1.f, 1.f,1.f,1.f,1.f, 0.f,0.f,0.f,1.f, 1.f,1.f,1.f,1.f, 0.f,0.f,0.f,1.f,
  1.f,1.f,1.f,1.f, 0.f,0.f,0.f,1.f, 1.f,1.f,1.f,1.f, 0.f,0.f,0.f,1.f, 1.f,1.f,1.f,1.f, 0.f,0.f,0.f,1.f, 1.f,1.f,1.f,1.f, 0.f,0.f,0.f,1.f,
  1.f,1.f,1.f,1.f, 0.f,0.f,0.f,1.f, 1.f,1.f,1.f,1.f, 0.f,0.f,0.f,1.f, 1.f,1.f,1.f,1.f, 0.f,0.f,0.f,1.f, 1.f,1.f,1.f,1.f, 0.f,0.f,0.f,1.f,
  1.f,1.f,1.f,1.f, 0.f,0.f,0.f,1.f, 1.f,1.f,1.f,1.f, 0.f,0.f,0.f,1.f, 1.f,1.f,1.f,1.f, 0.f,0.f,0.f,1.f, 1.f,1.f,1.f,1.f, 0.f,0.f,0.f,1.f,
  1.f,1.f,1.f,1.f, 0.f,0.f,0.f,1.f, 1.f,1.f,1.f,1.f, 0.f,0.f,0.f,1.f, 1.f,1.f,1.f,1.f, 0.f,0.f,0.f,1.f, 1.f,1.f,1.f,1.f, 0.f,0.f,0.f,1.f,
  1.f,1.f,1.f,1.f, 0.f,0.f,0.f,1.f, 1.f,1.f,1.f,1.f, 0.f,0.f,0.f,1.f, 1.f,1.f,1.f,1.f, 0.f,0.f,0.f,1.f, 1.f,1.f,1.f,1.f, 0.f,0.f,0.f,1.f,
};
/* this is static data @p.268. we'll do buffer reads from memory to textures in a moment. */
glTextureSubImage2D(texture_name, 0, 0, 0, texture_width, texture_height, GL_RGBA, GL_FLOAT, texture_checkerboard);
/* unit must be between 0 and GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS - 1 */
glBindTextureUnit(0, texture_name);

