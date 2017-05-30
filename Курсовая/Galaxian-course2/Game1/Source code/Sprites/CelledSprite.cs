using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;

namespace GalaxianGame
{
    public class CelledSprite : Sprite
    {
        /// <summary>
        /// Amount of cells at X-axis.
        /// </summary>
        private readonly int _cellsX;

        public Size CellSize { get; }

        public CelledSprite(int pCellsX, int pCellsY, Texture2D pTexture, Vector2 pPosition) : base(pTexture, pPosition)
        {
            _cellsX = pCellsX;

            CellSize = new Size
            {
                Height = Texture.Height / pCellsY,
                Width = Texture.Width / pCellsX
            };
        }

        public Rectangle GetCell(int pCellNumber)
        {
            int row    = pCellNumber / _cellsX;
            int column = pCellNumber % _cellsX;

            int positionInTextureX = CellSize.Width * column;
            int positionInTextureY = CellSize.Height * row;

            return new 
                Rectangle(positionInTextureX, positionInTextureY, CellSize.Width, CellSize.Height);
        }

        public virtual void Draw(SpriteBatch pSpriteBatch, Vector2 pPosition, int pCellNumber, float pScale = 1f)
        {
            Rectangle cell = GetCell(pCellNumber);
            pSpriteBatch.Draw(Texture, pPosition, cell, Color.White, 0f, Vector2.Zero, pScale, SpriteEffects.None, 0);
        }
    }
}