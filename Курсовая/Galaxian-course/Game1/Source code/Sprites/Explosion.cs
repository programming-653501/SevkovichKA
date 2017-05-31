using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Audio;
using Microsoft.Xna.Framework.Graphics;

namespace GalaxianGame
{
    public class Explosion : AnimatedSprite
    {
        private double _lastTextureChangeTime = 0;
        private readonly SoundEffect _boom;
        private readonly SpriteBatch _spriteBatch;
        private readonly bool _isPlayer;


        public Explosion(SpriteBatch pSpriteBatch, Vector2 pPosition, bool pIsPlayer = false)
            : base(GetTextures(pSpriteBatch, pIsPlayer), pPosition)
        {
            _boom = ContentManager.GetSoundEffect("Content\\SFX\\Boom.wav");
            _boom.Play();
            _currentFrame = 0;
            _spriteBatch = pSpriteBatch;
            _isPlayer = pIsPlayer;
            if (pIsPlayer)
                Position = new Vector2(Position.X - 22, Position.Y);
        }

        private static Texture2D[] GetTextures(SpriteBatch pSpriteBatch, bool pIsPlayer)
        {
            Texture2D[] textures = new Texture2D[3];

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
            if (_currentFrame == 3)
                return true;

            var timeNow = pGameTime.TotalGameTime.TotalMilliseconds;

            int delay = (_isPlayer) ? 250 : 100;

            if (timeNow - _lastTextureChangeTime > delay)
            {
                _currentFrame++;
                _lastTextureChangeTime = pGameTime.TotalGameTime.TotalMilliseconds;
            }

            return false;
        }
    }
}