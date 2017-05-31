using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;

namespace GalaxianGame
{
    public class OnGameScreen : IGamescreenable
    {
        private readonly GraphicsDevice _graphicsDevice;
        private readonly SpriteBatch _spriteBatch;
        private readonly InputManager _inputManager = new InputManager();
        private readonly DifficulityLevel _difficulityLevel;

        private int _timeLastChangeTimer;
        private PlayerSprite _playerSprite;
        private Sprite _heartSprite;
        private bool _isPlayerAlive = true;
        private Font _font;
        private int _score = 0;
        private int _givenTime = 200;
        private EnemyGrid _enemyGrid;
        private double _timeOfHeroDeath = 0;
        private bool _newBest = false;

        public bool IsEscapePressed { get; set; }
        public double TimeWhenPauseStops { get; set; } = -1;
        public bool Quit { get; set; } = false;

        public OnGameScreen(SpriteBatch pSpriteBatch, GameTime pGameTime, DifficulityLevel pDifficulityLevel)
        {
            _graphicsDevice = pSpriteBatch.GraphicsDevice;
            _spriteBatch = pSpriteBatch;
            _difficulityLevel = pDifficulityLevel;
            _timeLastChangeTimer = pGameTime.TotalGameTime.Seconds;
            _enemyGrid = new EnemyGrid(Vector2.Zero, 8, 5, pSpriteBatch, pDifficulityLevel, 2.2f);
        }

        public void LoadContent()
        {
            var heartTexture = ContentManager.GetTexture2D(_graphicsDevice, "Content\\Textures\\Heart.png");
            var playersTexture = ContentManager.GetTexture2D(_graphicsDevice, "Content\\Textures\\Hero\\Loaded.png");
            _playerSprite = new PlayerSprite
                (playersTexture, _difficulityLevel, new Vector2(380, 470), _graphicsDevice);

            var fontTexture = ContentManager.GetTexture2D(_graphicsDevice, "Content\\Font\\Font.png");
            var mapping = ContentManager.GetFontMapping("Content\\Font\\FontMapping.txt");
            var framedSprite = new CelledSprite(8, 6, fontTexture, Vector2.Zero);
            _font = new Font(framedSprite, mapping);

            _heartSprite = new Sprite(heartTexture, new Vector2(20, 550));
          }

        public void Update(GameTime pGameTime)
        {
            if (!_enemyGrid.IsAllDead() && _isPlayerAlive)
            {
                if (TimeWhenPauseStops == pGameTime.TotalGameTime.Seconds) return;

                TimeWhenPauseStops = -1;

                double TimeNow = pGameTime.TotalGameTime.TotalMilliseconds;
                if (TimeNow - _timeOfHeroDeath > 2500)
                {
                    _playerSprite.Active = true;
                }

                _playerSprite.Update(_inputManager, _graphicsDevice);

                if (_playerSprite.Active)
                {
                    _inputManager.Update();
                    AllCollisionsCheck(pGameTime); 
                }

                _enemyGrid.Update(pGameTime, _playerSprite);

                if (_playerSprite.OutOfScreen)
                {
                    ChangeScore(-5);
                    _playerSprite.OutOfScreen = false;
                }

                var timeNow = pGameTime.TotalGameTime.Seconds;
                if (timeNow != _timeLastChangeTimer && _givenTime > 0)
                    _givenTime--;

                if (_timeLastChangeTimer != pGameTime.TotalGameTime.Seconds)
                    _timeLastChangeTimer = pGameTime.TotalGameTime.Seconds;

                if (_inputManager.IsPressed(Input.Escape))
                    IsEscapePressed = true;
            }
            else
            {
                _inputManager.Update();

                if (_inputManager.IsPressed(Input.Enter))
                    Quit = true;
            }
        }

        public void ChangeScore(int pValue) => _score += pValue;

        private void AllCollisionsCheck(GameTime pGameTime)
        {
            if (_enemyGrid.PlayerShotCollision(_playerSprite.ShotSprite))
            {
                _playerSprite.GotEnemy = true;
                ChangeScore((_difficulityLevel == DifficulityLevel.Easy) ? 10 : 20);
            }

            if ((_enemyGrid.EnemyPlayerCollision(_playerSprite) || 
                _enemyGrid.EnemyShotCollision(_playerSprite, pGameTime)) && _playerSprite.Active)
            {
                _playerSprite.Active = false;
                _playerSprite.Lives--;
                _timeOfHeroDeath = pGameTime.TotalGameTime.TotalMilliseconds;

                if (_playerSprite.Lives == 0)
                    _isPlayerAlive = false;
            }
        }

        public void Draw(GameTime pGameTime)
        {
            if (!_enemyGrid.IsAllDead() && _isPlayerAlive)
            {
                _graphicsDevice.Clear(Color.TransparentBlack);
                _playerSprite.Draw(_spriteBatch, 1.3f);
                _enemyGrid.Draw();

                for (int i = 0; i < _playerSprite.Lives; ++i)
                {
                    var currentPosition = new Vector2(20 + (30 + _heartSprite.Texture.Width) * i, 
                        _heartSprite.Position.Y);

                    _heartSprite.Position = currentPosition;

                    _heartSprite.Draw(_spriteBatch, 3f);
                }

                _font.DrawString(_spriteBatch, "TIME", new Vector2(250, 550), 4f);
                _font.DrawString(_spriteBatch, _givenTime.ToString(), new Vector2(350, 550), 4f);

                _font.DrawString(_spriteBatch, "SCORE", new Vector2(510, 550), 4f);
                _font.DrawString(_spriteBatch, _score.ToString(), new Vector2(630, 550), 4f);   
            }
            else if (!_isPlayerAlive)
            {
                _spriteBatch.GraphicsDevice.Clear(Color.Black);
                _font.DrawString(_spriteBatch, "GAME OVER", new Vector2(270, 250), 4f);
                _font.DrawString(_spriteBatch, "PRESS ENTER TO EXIT", new Vector2(170, 290), 4f);
            }
            else
            {
                _spriteBatch.GraphicsDevice.Clear(Color.Black);
                _font.DrawString(_spriteBatch, "YOUR SCORE IS", new Vector2(170, 250), 4f);
                _font.DrawString(_spriteBatch, 552.ToString(),  new Vector2(460, 250), 4f);
                _font.DrawString(_spriteBatch, "NEW BEST!",     new Vector2(270, 290), 4f);
            }
        }
    }
}