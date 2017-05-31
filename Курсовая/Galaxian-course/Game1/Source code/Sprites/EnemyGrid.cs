using System;
using System.Collections.Generic;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Audio;
using Microsoft.Xna.Framework.Graphics;

namespace GalaxianGame
{
    public class EnemyGrid : AnimatedSprite
    {
        private EnemyAnimatedSprite[][] _enemies;
        private Vector2 _spacing = new Vector2(25, 25);
        private int _staticEnemySpeed = 2;
        private int _flyingEnemySpeed = 4;
        private int _startingPositionY = 50;
        private readonly SpriteBatch _spriteBatch;
        private Size _enemySize;
        private readonly float _scale;
        private Random rng = new Random();
        private SoundEffect _shot = ContentManager.GetSoundEffect("Content\\SFX\\EnemyShot.wav");
        private readonly Texture2D _enemyShotTexture;
        private List<(ShotSprite, EnemyAnimatedSprite)> _enemyShots 
            = new List<(ShotSprite, EnemyAnimatedSprite)>();
        private List<Explosion> _explosions = new List<Explosion>();
        private bool _isPlayerExplosionInList = false;
        public FlyingEnemy FlyingEnemy { get; private set; } = null;
        private DifficulityLevel _difficulityLevel;
        
        public bool EndGame { get; }

        public EnemyGrid(Vector2 pPosition, int pGridRows, int pGridColumns, SpriteBatch pSpriteBatch, 
           DifficulityLevel pDifficulityLevel, float pScale) 
            : base(GetTextures(pDifficulityLevel, pSpriteBatch), pPosition)
        {
            _spriteBatch = pSpriteBatch;
            _scale = pScale;
            _difficulityLevel = pDifficulityLevel;

            _enemies = new EnemyAnimatedSprite[pGridRows][];
            for (int i = 0; i < _enemies.Length; ++i)
            {
                _enemies[i] = new EnemyAnimatedSprite[pGridColumns];
            }

            _enemySize = new Size
            {
                Height = (int)(Textures[_currentFrame].Height * pScale),
                Width  = (int)(Textures[_currentFrame].Width  * pScale)
            };

            var position = new Vector2(GalaxianGame.WindowSize.Width / 2 -
                pGridColumns * (_enemySize.Width + _spacing.X) / 2, _startingPositionY);

            Position = position;
            _enemyShotTexture = ContentManager.GetTexture2D(_spriteBatch.GraphicsDevice,
                    "Content\\Textures\\Enemy\\LaserShot.png");

            for (int i = 0; i < pGridRows; ++i)
            {
                for (int j = 0; j < pGridColumns; ++j)
                {
                    var enemyPosition = new Vector2(Position.X + i * (_enemySize.Width + _spacing.X), 
                       Position.Y + j * (_enemySize.Height + _spacing.Y));

                    _enemies[i][j] = new EnemyAnimatedSprite(GetTextures(pDifficulityLevel, pSpriteBatch),
                        enemyPosition, pSpriteBatch, pDifficulityLevel);
                }
            }
        }

        private static Texture2D[] GetTextures(DifficulityLevel pDifficulityLevel, SpriteBatch pSpriteBatch)
        {
            Texture2D[] textures = new Texture2D[3];

            var level = (pDifficulityLevel == DifficulityLevel.Easy) ? "Easy" : "Hard";
            for (int i = 0; i < textures.Length; ++i)
            {
                var fileName = level + (i + 1) + ".png";
                textures[i] = ContentManager.GetTexture2D(pSpriteBatch.GraphicsDevice,
                    "Content\\Textures\\Enemy\\" + fileName);
            }

            return textures;
        }

        public void Update(GameTime pGameTime, PlayerSprite pPlayer)
        {
            if (IsAllDead()) return;

            if (pPlayer.Active)
            {
                var rightest = FindRightest();
                var leftest = FindLeftest();

                var rightBorderReached = rightest?.Position.X + _enemySize.Width >= GalaxianGame.WindowSize.Width;
                var leftBorderReached = leftest?.Position.X <= 0;

                if (rightest != null  && (rightBorderReached || leftBorderReached))
                    _staticEnemySpeed *= -1;

                for (int i = 0; i < _enemies.Length; ++i)
                {
                    for (int j = 0; j < _enemies[i].Length; ++j)
                    {
                        if (_enemies[i][j] != null && _enemies[i][j] != FlyingEnemy)
                        {
                            var newEnemyPosition = new Vector2(_enemies[i][j].Position.X + _staticEnemySpeed,
                                _enemies[i][j].Position.Y);

                            _enemies[i][j].Position = newEnemyPosition;
                            _enemies[i][j].Update(pGameTime, _spriteBatch.GraphicsDevice);
                        }
                    }
                }

                if (rng.NextDouble() > 0.935f)
                {
                    var x = (int) (rng.NextDouble() * _enemies.Length);
                    var y = (int) (rng.NextDouble() * _enemies[0].Length);

                    while (_enemies[x][y] == null)
                    {
                        x = (int)(rng.NextDouble() * _enemies.Length);
                        y = (int)(rng.NextDouble() * _enemies[0].Length);
                    }

                    var shotPosition = new Vector2(_enemies[x][y].Position.X + _enemySize.Width / 2, 
                        _enemies[x][y].Position.Y + _enemySize.Height);

                    var shot = new ShotSprite(_enemyShotTexture, shotPosition, 7);
                    shot.IsFlying = true;
                    _enemyShots.Add(new ValueTuple<ShotSprite, EnemyAnimatedSprite>(shot, _enemies[x][y]));
                    _shot.Play();
                }

                if (rng.NextDouble() > 0.9f && FlyingEnemy == null)
                {
                    FlyingEnemy = new FlyingEnemy(_enemies, _spriteBatch, _difficulityLevel, pPlayer.Position);
                    var x = (int) FlyingEnemy.CoordsInGrid.X;
                    var y = (int) FlyingEnemy.CoordsInGrid.Y;
                    _enemies[x][y] = null;
                }

                var gridPosition = new Vector2(Position.X + _staticEnemySpeed, Position.Y);
                Position = gridPosition;
            }

            if (FlyingEnemy != null)
            {
                FlyingEnemy.Update(pGameTime, Position);

                if (FlyingEnemy.HasComeBack)
                {
                    var x = (int) FlyingEnemy.CoordsInGrid.X;
                    var y = (int) FlyingEnemy.CoordsInGrid.Y;
                    _enemies[x][y] = FlyingEnemy;
                    FlyingEnemy = null;
                }
            }

            for (int i = 0; i < _enemyShots.Count; ++i)
            {
                AnimatedSprite sender = _enemyShots[i].Item2;
                _enemyShots[i].Item1.Update(sender);

                if (_enemyShots[i].Item1.Position.Y > GalaxianGame.WindowSize.Height)
                    _enemyShots.RemoveAt(i);
            }

            if (!pPlayer.Active && _explosions.Count > 0)
                if (_explosions[0].Update(pGameTime))
                {
                    _explosions.RemoveAt(0);
                    _isPlayerExplosionInList = false;
                }

            for (int i = 0; i < _explosions.Count; ++i)
            {
                if (i == 0 && _isPlayerExplosionInList) continue;

                if (_explosions[i].Update(pGameTime))
                    _explosions.RemoveAt(i);
            }
        }

        private EnemyAnimatedSprite FindLeftest()
        {
            for (int i = 0; i < _enemies.Length; ++i)
            {
                for (int j = 0; j < _enemies[i].Length; ++j)
                {
                    if (_enemies[i][j] != null)
                        return _enemies[i][j];
                }
            }

            return null;
        }

        private EnemyAnimatedSprite FindRightest()
        {
            for (int i = _enemies.Length - 1; i >= 0 ; --i)
            {
                for (int j = _enemies[i].Length - 1; j >= 0 ; --j)
                {
                    if (_enemies[i][j] != null)
                        return _enemies[i][j];
                }
            }

            return null;
        }

        public bool IsAllDead() => FindRightest() == null;

        public bool PlayerShotCollision(ShotSprite pShot)
        {
            for (int i = 0; i < _enemies.Length; i++)
            {
                for (int j = 0; j < _enemies[i].Length; j++)
                {
                    if (_enemies[i][j] != null && CheckCollisionShot(pShot, _enemies[i][j]))
                    {
                        _enemies[i][j].Lives--;
                        if (_enemies[i][j].Lives == 0)
                        {
                            var explosion = new Explosion(_spriteBatch, _enemies[i][j].Position);
                            _explosions.Insert(0, explosion);
                            _enemies[i][j] = null;
                            return true;
                        }
                    }
                }
            }

            if (FlyingEnemy != null && CheckCollisionShot(pShot, FlyingEnemy))
            {
                FlyingEnemy.Lives--;
                if (FlyingEnemy.Lives == 0)
                {
                    var explosion = new Explosion(_spriteBatch, FlyingEnemy.Position);
                    _explosions.Insert(0, explosion);
                    FlyingEnemy = null;
                    return true;
                }
            }

            return false;
        }

        public bool EnemyShotCollision(PlayerSprite pPlayer, GameTime pGameTime)
        {
            for (int i = 0; i < _enemyShots.Count; i++)
            {
                if (CheckCollisionShot(_enemyShots[i].Item1, pPlayer: pPlayer))
                {
                    var explosion = new Explosion(_spriteBatch, pPlayer.Position, true);
                    _explosions.Insert(0, explosion);
                    _isPlayerExplosionInList = true;
                    _enemyShots.RemoveAt(i);
                    return true;
                }
            }

            return false;
        }

        public bool EnemyPlayerCollision(PlayerSprite pPlayer)
        { 
            if (FlyingEnemy != null && CheckCollisionShot(pEnemy: FlyingEnemy, pPlayer: pPlayer))
            {
                var playerExplosion = new Explosion(_spriteBatch, pPlayer.Position, true);
                var enemyExplosion  = new Explosion(_spriteBatch, FlyingEnemy.Position);
                _explosions.Add(playerExplosion);
                _isPlayerExplosionInList = true;
                FlyingEnemy = null;
                return true;
            }
             
            return false;
        }

        public bool CheckCollisionShot(ShotSprite pShot = null, AnimatedSprite pEnemy = null, Sprite pPlayer = null) =>
            pShot?.PositionBox.Intersects(pPlayer?.PositionBox ?? pEnemy.PositionBox) ??
            pEnemy.PositionBox.Intersects(pPlayer.PositionBox);

        public void Draw()
        {
            for (var i = 0; i < _enemies.Length; i++)
            {
                for (var j = 0; j < _enemies[i].Length; j++)
                {
                    _enemies[i][j]?.Draw(_spriteBatch, _scale);
                }
            }

            FlyingEnemy?.Draw(_spriteBatch, 2.2f);

            foreach (var shot in _enemyShots)
                shot.Item1.Draw(_spriteBatch);

            foreach (var explosion in _explosions)
                explosion.Draw(_spriteBatch);
        }
    }
}