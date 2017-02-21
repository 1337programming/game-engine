#ifndef GAME_ENGINE_SPRITEBATCH_H
#define GAME_ENGINE_SPRITEBATCH_H

#include <OpenGL/gl3.h>
#include <glm/glm.hpp>
#include <vector>
#include "Vertex.h"
#include "Color.h"

namespace Engine {

  enum class GlyphSortType {
      NONE,
      FRONT_TO_BACK,
      BACK_TO_FRONT,
      TEXTURE
  };

  struct Glyph {
    GLuint texture;
    float depth;
    Vertex topLeft;
    Vertex bottomLeft;
    Vertex topRight;
    Vertex bottomRight;
  };

  class RenderBatch {

    public:
      RenderBatch(GLuint offst, GLuint nVerts, GLuint txtr) : offset(offst), numVertices(nVerts), texture(txtr) {}

      GLuint offset;
      GLuint numVertices;
      GLuint texture;
  };

  class SpriteBatch {

    public:

      SpriteBatch();

      ~SpriteBatch();

      void init();

      void begin(GlyphSortType sortType = GlyphSortType::TEXTURE);

      void end();

      void draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture, float depth, const Color& color);

      void renderBatch();

    private:
      void createRenderBatches();

      void createVertexArray();

      void sortGlyphs();

      static bool compareFrontToBack(Glyph* a, Glyph* b);

      static bool compareBackToFront(Glyph* a, Glyph* b);

      static bool compareTexture(Glyph* a, Glyph* b);

      GLuint _vbo;
      GLuint _vao;

      GlyphSortType _sortType;

      std::vector<Glyph*> _glyphs;
      std::vector<RenderBatch> _renderBatches;

  };

}

#endif //GAME_ENGINE_SPRITEBATCH_H
