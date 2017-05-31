using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;

namespace GalaxianGame
{
    public abstract class AnimatedSprite
    {
        public Texture2D[] Textures { get; }
        public Vector2 Position { get; set; }
        public Rectangle PositionBox { get; set; }
        protected int _currentFrame;

        protected AnimatedSprite(Texture2D[] pTexture, Vector2 pPosition)
        {
            Textures = pTexture;
            Position = pPosition;

            PositionBox = new Rectangle((int)Position.X, (int)Position.Y, 
                Textures[_currentFrame].Width, Textures[_currentFrame].Height);
        }

        public AnimatedSprite()
        {
        }

        public virtual void Draw(SpriteBatch pSpriteBatch, float pScale = 1f)
        {
            if (_currentFrame < 3)
                pSpriteBatch.Draw(Textures[_currentFrame], Position, scale: new Vector2(pScale, pScale));
        }
}
}