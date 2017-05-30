using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;

namespace GalaxianGame
{
    public class Sprite
    {
        public Texture2D Texture { get; set; }
        public Vector2 Position { get; set; }
        public Rectangle PositionBox { get; set; }

        public Sprite(Texture2D pTexture, Vector2 pPosition)
        {
            Texture = pTexture;
            Position = pPosition;

            PositionBox = new Rectangle((int)Position.X, (int)Position.Y, Texture.Width, Texture.Height);
        }

        public virtual void Draw(SpriteBatch pSpriteBatch, float pScale = 1f) => 
            pSpriteBatch.Draw(Texture, Position, scale:new Vector2(pScale, pScale));
    }
}