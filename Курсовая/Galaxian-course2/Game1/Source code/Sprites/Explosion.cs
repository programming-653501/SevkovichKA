using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Audio;
using Microsoft.Xna.Framework.Graphics;

namespace GalaxianGame
{
    public class Explosion : AnimatedSprite
    {
        private double _lastTextureChangeTime = 0;
        private readonly SoundEffect _boom;


        public Explosion(SpriteBatch pSpriteBatch, Vector2 pPosition, bool pIsPlayer = false)
            : base(GetTextures(pSpriteBatch, pIsPlayer), pPosition)
        {
            _boom = ContentManager.GetSoundEffect("Content\\SFX\\Boom.wav");
            _boom.Play();
            _currentFrame = 0;
        }

        private static Texture2D[] GetTextures(SpriteBatch pSpriteBatch, bool pIsPlayer)
        {
            Texture2D[] textures = new Texture2D[5];

            for (int i = 0; i < textures.Length; ++i)
            {
                var fileName = (pIsPlayer) ? "Hero\\" : "Enemy\\";
                fileName += "Explosion" + (i + 1) + ".png";

                textures[i] = ContentManager.GetTexture2D(pSpriteBatch.GraphicsDevice,
                    "Content\\Textures\\" + fileName);
            }

            return textures;
        }

        public bool Update(GameTime pGameTime)
        {
            if (_currentFrame == 5)
                return true;

            var timeNow = pGameTime.TotalGameTime.TotalMilliseconds;

            if (timeNow - _lastTextureChangeTime > 50)
            {
                _currentFrame++;
                _lastTextureChangeTime = pGameTime.TotalGameTime.TotalMilliseconds;
            }

            return false;
        }
    }
}