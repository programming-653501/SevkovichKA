using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;

namespace GalaxianGame
{
    /// <summary>
    /// Main game class.
    /// </summary>
    public class GalaxianGame : Game
    {
        public GraphicsDeviceManager Graphics;
        private SpriteBatch _spriteBatch;
        private IntroScreen _introScreen;
        private OnGameScreen _onGameScreen;
        private PauseScreen _pauseScreen;
        private Gamescreen _currentGamescreen;

        public static Size WindowSize { get; private set; } = new Size()
        {
            Height = 600,
            Width = 800
        };

        public GalaxianGame()
        {
            Graphics = new GraphicsDeviceManager(this)
            {
                PreferredBackBufferWidth = WindowSize.Width,
                PreferredBackBufferHeight = WindowSize.Height
            };

            Content.RootDirectory = "Content";
            Window.Title = "Galaxian";
            _currentGamescreen = Gamescreen.IntroScreen;
        }

        /// <summary>
        /// Allows the game to perform any initialization it needs to before starting to run.
        /// </summary>
        protected override void Initialize()
        {
            _spriteBatch = new SpriteBatch(GraphicsDevice);
            _introScreen = new IntroScreen(_spriteBatch);
            base.Initialize();
        }

        /// <summary>
        /// Called once per game for loading all needed content.
        /// </summary>
        protected override void LoadContent()
        {
            _introScreen.LoadContent();
        }

        /// <summary>
        /// Allows the game to run logic.
        /// </summary>
        protected override void Update(GameTime gameTime)
        {
            switch(_currentGamescreen)
            {
                case Gamescreen.IntroScreen:
                {
                    _introScreen.Update(gameTime);

                    if (_introScreen.IsEnterPressed)
                    {
                        _onGameScreen = new OnGameScreen(_spriteBatch, gameTime, _introScreen.DifficulityLevel);
                        _onGameScreen.LoadContent();
                        _currentGamescreen = Gamescreen.GameScreen;
                    }

                    if (_introScreen.IsEscapePressed)
                        Exit();

                    break;
                }
                case Gamescreen.GameScreen:
                {
                    _onGameScreen.Update(gameTime);

                    if (_onGameScreen.IsEscapePressed)
                    {
                        _pauseScreen = new PauseScreen(_spriteBatch, gameTime);
                        _pauseScreen.LoadContent();
                        _currentGamescreen = Gamescreen.PauseScreen;
                    }

                    if (_onGameScreen.Quit)
                        Exit();

                    break;
                }
                case Gamescreen.PauseScreen:
                {
                    _pauseScreen.Update(gameTime);

                    if (_pauseScreen.IsBackChosen)
                    {
                        _currentGamescreen = Gamescreen.GameScreen;
                        _onGameScreen.TimeWhenPauseStops = gameTime.TotalGameTime.Seconds;
                        _onGameScreen.IsEscapePressed = false;
                    }
                    else if (_pauseScreen.IsQuitChosen)
                        Exit();

                    break;
                }
            }
            base.Update(gameTime);
        }

        /// <summary>
        /// Draws on screen.
        /// </summary>
        protected override void Draw(GameTime gameTime)
        {
            _spriteBatch.Begin(samplerState: SamplerState.PointWrap);

            switch (_currentGamescreen)
            {
                case Gamescreen.IntroScreen:
                    _introScreen.Draw(gameTime); break;
                case Gamescreen.GameScreen:
                    _onGameScreen.Draw(gameTime); break;
                case Gamescreen.PauseScreen:
                    _pauseScreen.Draw(gameTime); break;
            }

            _spriteBatch.End();

            base.Draw(gameTime);
        }
    }
}
