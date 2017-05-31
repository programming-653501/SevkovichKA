using System;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;

namespace GalaxianGame
{
    public class FlyingEnemy : EnemyAnimatedSprite
    {
        public bool HasReachedBottom { get; set; } = false;
        public bool HasComeBack { get; set; } = false;
        public  Vector2 CoordsInGrid { get; }
        private Vector2 _positionInGrid;
        private Vector2 _coordsOnTop;
        private Vector2 _targetPosition;
        private readonly SpriteBatch _spriteBatch;

        public FlyingEnemy(EnemyAnimatedSprite[][] pEnemies, SpriteBatch pSpriteBatch, 
            DifficulityLevel pDifficulityLevel, Vector2 pTargetPosition) : 
            base(GetTextures(pSpriteBatch, pDifficulityLevel), Vector2.One, pSpriteBatch, pDifficulityLevel)
        {
            _spriteBatch = pSpriteBatch;
            _targetPosition.X = pTargetPosition.X;
            _targetPosition.Y = GalaxianGame.WindowSize.Height + 10;

            Random rng = new Random();

            var x = (int)(rng.NextDouble() * pEnemies.Length);
            var y = (int)(rng.NextDouble() * pEnemies[0].Length);

            while (pEnemies[x][y] == null)
            {
                x = (int)(rng.NextDouble() * pEnemies.Length);
                y = (int)(rng.NextDouble() * pEnemies[0].Length);
            }

            Position = pEnemies[x][y].Position;

            CoordsInGrid = new Vector2(x, y);
        }

        private static Texture2D[] GetTextures(SpriteBatch pSpriteBatch, DifficulityLevel pDifficulityLevel)
        {
            Texture2D[] textures = new Texture2D[3];

            for (int i = 0; i < textures.Length; ++i)
            {
                var fileName = (pDifficulityLevel == DifficulityLevel.Easy) ? "Easy" : "Hard";
                fileName += (i + 1) + ".png";

                textures[i] = ContentManager.GetTexture2D(pSpriteBatch.GraphicsDevice,
                    "Content\\Textures\\Enemy\\" + fileName);
            }

            return textures;
        }

        public void Update(GameTime pGameTime, Vector2 pGridPosition)
        {
            base.Update(pGameTime, _spriteBatch.GraphicsDevice);

            Vector2 direction;

            if (!HasReachedBottom)
            {
                direction = Vector2.Normalize(_targetPosition - Position);

                if (Position.Y >= GalaxianGame.WindowSize.Height)
                {
                    Position = new Vector2(Position.X, 0);
                    HasReachedBottom = true;
                    _coordsOnTop = Position;
                }

                Position += direction * 5;
            }
            else
            {
                _positionInGrid.X = pGridPosition.X + CoordsInGrid.X * (Textures[0].Width * 2.2f  + 25);
                _positionInGrid.Y = pGridPosition.Y + CoordsInGrid.Y * (Textures[0].Height * 2.2f + 25);
                
                HasComeBack = true;
                Position = _positionInGrid;
            }
        }
    }
}