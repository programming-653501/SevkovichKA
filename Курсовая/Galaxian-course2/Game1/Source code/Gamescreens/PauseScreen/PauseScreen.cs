using System;
using System.Collections.Generic;
using System.IO;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;

namespace GalaxianGame
{
    class PauseScreen : IGamescreenable
    {
        private enum Option
        {
            Back,
            Quit
        }

        private readonly GraphicsDevice _graphicsDevice;
        private readonly SpriteBatch _spriteBatch;
        private readonly InputManager _inputManager = new InputManager();
        private readonly double _timeOnCreenStart;

        private Font _font;
        private Option _option = Option.Back;
        private bool _wasPressedUpOrDown = false;
        private double _timeWhenPressedUpOrDown;
        private bool _on = false;
        private List<PlayerScore> _playerScores = new List<PlayerScore>();

        private const int DelayInMilliseconds = 200;

        public bool IsQuitChosen { get; private set; } = false;
        public bool IsBackChosen { get; set; } = false;

        public PauseScreen(SpriteBatch pSpriteBatch, GameTime pGameTime)
        {
            _graphicsDevice = pSpriteBatch.GraphicsDevice;
            _spriteBatch = pSpriteBatch;
            _timeOnCreenStart = pGameTime.TotalGameTime.Seconds;
        }

        public void LoadContent()
        {
            var fontTexture = ContentManager.GetTexture2D(_graphicsDevice, "Content\\Font\\Font.png");
            var mapping = ContentManager.GetFontMapping("Content\\Font\\FontMapping.txt");
            var framedSprite = new CelledSprite(8, 6, fontTexture, Vector2.Zero);
            _font = new Font(framedSprite, mapping);

            using (StreamReader sr = new StreamReader("Content\\Saves\\HighScores.txt", System.Text.Encoding.Default))
            {
                var text = sr.ReadToEnd();
                var lines = text.Split('\n');
                var listSize = lines.Length / 2;

                for (int i = 0; i < listSize; ++i)
                {
                    var playersScore = new PlayerScore
                    {
                        Name = lines[i * 2],
                        Score = lines[i * 2 + 1]
                    };
                
                    _playerScores.Add(playersScore);
                }
            }
        }

        public void Update(GameTime pGameTime)
        {
            if (!_on)
            {
                var _timeFromCreenStart = pGameTime.TotalGameTime.Seconds;
                if (_timeFromCreenStart == _timeOnCreenStart) return;
                _on = true;
            }

            _inputManager.Update();

            if (_inputManager.IsPressed(Input.Escape))
                IsBackChosen = true;

            if (_inputManager.IsPressed(Input.Enter))
            {
                if (_option == Option.Back)
                    IsBackChosen = true;
                else
                    IsQuitChosen = true;
            }

            if (_inputManager.IsPressed(Input.MoveUp) || _inputManager.IsPressed(Input.MoveDown))
            {
                if (!_wasPressedUpOrDown)
                {
                    _option = ((_option == Option.Back) ? Option.Quit : Option.Back);
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
            _font.DrawString(_spriteBatch, "PAUSE MENU", new Vector2(275, 50), 5f);
            _font.DrawString(_spriteBatch, "BACK", new Vector2(100, 250), 3f);
            _font.DrawString(_spriteBatch, "QUIT", new Vector2(100, 300), 3f);
            _font.DrawString(_spriteBatch, "COURSE PROJECT MADE BY KYRIL SIAUKOVICH", new Vector2(400, 580), 2f);
            _font.DrawString(_spriteBatch, ">", new Vector2(70, (_option == Option.Back) ? 250 : 300), 3f);
            _font.DrawString(_spriteBatch, "BEST RESULTS", new Vector2(400, 180), 4f);
            

            if (_playerScores.Count == 0)
                _font.DrawString(_spriteBatch, "NO BEST RESULTS YET", new Vector2(400, 220), 3f);
            else
            {
                _font.DrawString(_spriteBatch, "NAME",  new Vector2(450, 240), 3f);
                _font.DrawString(_spriteBatch, "SCORE", new Vector2(570, 240), 3f);

                for (var i = 0; i < _playerScores.Count ;i++)
                {
                    _font.DrawString(_spriteBatch, (i + 1) + ".", new Vector2(380, 290 + 40 * i), 3f);
                    _font.DrawString(_spriteBatch, _playerScores[i].Name,  new Vector2(450, 290 + 40 * i), 3f);
                    _font.DrawString(_spriteBatch, _playerScores[i].Score, new Vector2(580, 290 + 40 * i), 3f);
                }
            }
        }
    }
}
