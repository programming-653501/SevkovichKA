using System;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;

namespace GalaxianGame
{
    public class EnemyAnimatedSprite : AnimatedSprite
    {
        public int Lives { get; set; }

        private int _changeFrameStep = 1;
        private double _lastTextureChangeTime = 0;

        private readonly SpriteBatch _spriteBatch;

        private static readonly Random Rng = new Random();

        public EnemyAnimatedSprite(Texture2D[] pTextures, Vector2 pPosition,
             SpriteBatch pSpriteBatch, DifficulityLevel pDifficulityLevel) : base(pTextures, pPosition)
        {
            _spriteBatch = pSpriteBatch;
            Lives = (pDifficulityLevel == DifficulityLevel.Easy) ? 1 : 2;
            _currentFrame = Rng.Next(0, 3);
        }

        protected EnemyAnimatedSprite() : base()
        {}

        public void Update(GameTime pGameTime, GraphicsDevice pGraphicsDevice)
        {
            if (_currentFrame == 2) 
                _changeFrameStep = -1;

            if (_currentFrame == 0)
                _changeFrameStep = 1;

            var timeNow = pGameTime.TotalGameTime.TotalMilliseconds;
            if (timeNow - _lastTextureChangeTime > 100)
            {
                _lastTextureChangeTime = timeNow;
                _currentFrame += _changeFrameStep;
            }

            PositionBox = new Rectangle((int)Position.X, (int)Position.Y,
                (int)(Textures[_currentFrame].Width * 2.2f), (int)(Textures[_currentFrame].Height * 2.2f));
        }
    }
}