using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;

namespace GalaxianGame
{
    public class ShotSprite : Sprite
    {
        //speed along the Y-axis
        private readonly int _speedY;
        public bool IsFlying { get; set; } = false;

        public ShotSprite(Texture2D pTexture, Vector2 pPosition, int pSpeedY)
            : base(pTexture, pPosition)
        {
            _speedY = pSpeedY;
        }

        public void Update(Sprite pShooter) => 
            Update(pShooter.Texture.Width, pShooter.Texture.Height, pShooter.Position);
        
        public void Update(AnimatedSprite pShooter) => 
            Update(pShooter.Textures[0].Width, pShooter.Textures[0].Height, pShooter.Position);

        private void Update(int pTextureWidth, int pTextureHeight, Vector2 pPosition)
        {
            var currentPosition = Position;
            if (!IsFlying)
            {
                currentPosition.X = pPosition.X + pTextureWidth / (float)2 + 2;
                currentPosition.Y = pPosition.Y - pTextureHeight;
            }
            else
                currentPosition.Y += _speedY;

            Position = currentPosition;
            PositionBox = new Rectangle((int)Position.X, (int)Position.Y, Texture.Width, Texture.Height);
        }

        public override void Draw(SpriteBatch pSpriteBatch, float pScale = 1)
        {
            if (IsFlying)
                base.Draw(pSpriteBatch, pScale);
        }
    }
}