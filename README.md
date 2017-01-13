Esta é minha pequena tentativa de fazer algo com o Modern OpenGL e a linguagem C ( C puro mesmo), estou projetando uma pequena engine/framework para jogos 2D. Estou me baseando bastante em engines/frameworks que já uso, como o GameMaker:Studio e o Love2D, por exemplo, tentando usar suas estruturas como base.

Assets usados para test:
- Imagens achadas na internet; xD
- Fonte `Early GameBoy` do [`Jimmy Campbell`](http://www.dafont.com/pt/jimmy-campbell.d5241)

Biblioteca de terceiros que estou usando:
- [`SDL2`](https://www.libsdl.org/) para criar um Contexto OpenGL
- [`stb_image`](https://github.com/nothings/stb) para carregar as imagens
- [`linmath`](https://github.com/datenwolf/linmath.h) para usar operações de algebra linear com vetores e matrizes.
- [`GLEW`](http://glew.sourceforge.net/) para acessar funções das versões mais novas do OpenGL.

# Engine

![Selene Engine](https://raw.githubusercontent.com/canoi12/selene/master/assets/animation.gif)

![Selene Engine](https://raw.githubusercontent.com/canoi12/canoi12.github.io/master/ImagensSite/selene_engine.png)

# SpriteBatch funcionando (renderizando 250000 objetos a 200 fps):

![Sele Engine](https://raw.githubusercontent.com/canoi12/selene/master/assets/spritebatch.gif)

# DEPENDÊNCIAS
- `SDL2`
- `SDL2_ttf`
- `GLEW`

# TODOS
- [ ] Adicionar suporte a sons.
- [x] Implementar Sprite Batch para otimizar drawcalls. (porém ainda é bem simples, vou revisar, e ver possíveis melhorias)
- [x] Adicionar suporte a fontes ttf. (Usando SDL2_ttf)
- [ ] Adicionar suporte a sprite fonts.
- [ ] Implementar loader de mapas .tmx do Tiled.
- [ ] Organizar melhor o código e a estrutura da engine.
- [ ] O que mais eu lembrar.