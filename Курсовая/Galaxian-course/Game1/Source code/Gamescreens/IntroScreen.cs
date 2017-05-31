using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;

namespace GalaxianGame
{
    class IntroScreen : IGamescreenable
    {
        private readonly GraphicsDevice _graphicsDevice;
        private readonly SpriteBatch _spriteBatch;
        private readonly InputManager _inputManager;
        private Font _font;
        private bool _wasPressedUpOrDown;
        private double _timeWhenPressedUpOrDown;

        public bool IsEnterPressed { get; private set; }
        public bool IsEscapePressed { get; private set; }
        public DifficulityLevel DifficulityLevel { get; private set; }

        private const int DelayInMilliseconds = 200;

        public IntroScreen(SpriteBatch pSpriteBatch)
        {
            IsEnterPressed = false;
            IsEscapePressed = false;
            DifficulityLevel = DifficulityLevel.Easy;
            _graphicsDevice = pSpriteBatch.GraphicsDevice;
            _spriteBatch = pSpriteBatch;
            _inputManager = new InputManager();
            _wasPressedUpOrDown = false;
        }

        public void LoadContent()
        {
            var fontTexture = ContentManager.GetTexture2D(_graphicsDevice, "Content\\Font\\Font.png");
            var mapping = ContentManager.GetFontMapping("Content\\Font\\FontMapping.txt");
            var framedSprite = new CelledSprite(8, 6, fontTexture, Vector2.Zero);
            _font = new Font(framedSprite, mapping);
        }

        public void Update(GameTime pGameTime)
        {
            _inputManager.Update();

            if (_inputManager.IsPressed(Input.Enter))
                IsEnterPressed = true;

            if (_inputManager.IsPressed(Input.Escape))
                IsEscapePressed = true;

            if (_inputManager.IsPressed(Input.MoveUp) || _inputManager.IsPressed(Input.MoveDown))
            {
                if (!_wasPressedUpOrDown)
                {
                    DifficulityLevel = ( (DifficulityLevel == DifficulityLevel.Easy) ?
                        DifficulityLevel.Hard : DifficulityLevel.Easy);

                    _timeWhenPressedUpOrDown = pGameTime.TotalGameTime.TotalMilliseconds;
                    _wasPressedUpOrDown = true;
                }
                else
                {
                    var currentTime = pGameTime.TotalGameTime.TotalMilliseconds;
                    if (currentTime - _timeWhenPressedUpOrDown > DelayInMilliseconds)
                        _wasPressedUpOrDown = false;
                }
            }
        }

        public void Draw(GameTime pGameTime)
        {
            _graphicsDevice.Clear(Color.Black);
            _font.DrawString(_spriteBatch, "GALAXIAN", new Vector2(250, 50), 7f);
            _font.DrawString(_spriteBatch, "CONTROLS", new Vector2(140, 150), 3f);
            _font.DrawString(_spriteBatch, "MOVE LEFT - ARROW LEFT", new Vector2(40, 200), 3f);
            _font.DrawString(_spriteBatch, "MOVE RIGHT - ARROW RIGHT", new Vector2(25, 250), 3f);
            _font.DrawString(_spriteBatch, "SHOOT - SPACEBAR", new Vector2(100, 300), 3f);
            _font.DrawString(_spriteBatch, "MENU - ESCAPE", new Vector2(115, 350), 3f);
            _font.DrawString(_spriteBatch, "PRESS ENTER TO BEGIN GAME", new Vector2(50, 440), 5f);
            _font.DrawString(_spriteBatch, "OR PRESS ESCAPE TO LEAVE YOUR GALAXY...", new Vector2(10, 500), 4f);
            _font.DrawString(_spriteBatch, "COURSE PROJECT MADE BY KYRIL SIAUKOVICH", new Vector2(400, 580), 2f);
            _font.DrawString(_spriteBatch, "CHOOSE DIFFICULITY", new Vector2(450, 180), 3f);
            _font.DrawString(_spriteBatch, "USING ARROWS", new Vector2(490, 210), 3f);
            _font.DrawString(_spriteBatch, "EASY", new Vector2(550, 250), 3f);
            _font.DrawString(_spriteBatch, "HARD", new Vector2(550, 280), 3f);
            _font.DrawString(_spriteBatch, ">", new Vector2(520, 
                (DifficulityLevel == DifficulityLevel.Easy) ? 250 : 280), 3f);
        }
    }
}
