using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Audio;
using Microsoft.Xna.Framework.Graphics;

namespace GalaxianGame
{
    public class PlayerSprite : Sprite
    {
        private readonly Texture2D _textureLoaded;
        private readonly Texture2D _textureUnloaded;
        private readonly SoundEffect _playerShot;

        public ShotSprite ShotSprite { get; }
        public bool GotEnemy { get; set; } = false;
        public bool OutOfScreen { get; set; } = false;
        public bool Active { get; set; } = true;

        private bool _loaded = true;
        private bool _spaceCouldBePressed = true;

        public int Lives { get; set; }

        public PlayerSprite(Texture2D pTexture, DifficulityLevel pDifficulityLevel, Vector2 pPosition, //  Content\\Textures\\Hero.png
            GraphicsDevice pGraphicsDevice): base(pTexture, pPosition)
        {
            Lives = (pDifficulityLevel == DifficulityLevel.Easy) ? 3 : 1;

            _textureLoaded = pTexture;

            _playerShot = ContentManager.GetSoundEffect("Content\\SFX\\PlayerShot.wav");
            _textureUnloaded = ContentManager.GetTexture2D(pGraphicsDevice, "Content\\Textures\\Hero\\Unloaded.png");
            var shotTexture  = ContentManager.GetTexture2D(pGraphicsDevice, "Content\\Textures\\Hero\\LaserShot.png");

            ShotSprite = new ShotSprite(shotTexture, new Vector2(Position.X + Texture.Width/2f, Position.Y), -10);
        }

        public void Update(InputManager pInputManager, GraphicsDevice pGraphicsDevice)
        {
            ShotSprite.Update(this);

            if (!Active) return;

            var currentPosition = Position;
            const int speed = 5;

            if (pInputManager.IsPressed(Input.MoveLeft) && currentPosition.X > 0)
                currentPosition.X -= speed;

            var windowWidth = pGraphicsDevice.PresentationParameters.BackBufferWidth;
            if (pInputManager.IsPressed(Input.MoveRight) && currentPosition.X < windowWidth - Texture.Width * 1.3f)
                currentPosition.X += speed;

            Position = currentPosition;

            if (_loaded && !pInputManager.IsPressed(Input.Shoot))
                _spaceCouldBePressed = true;

            if (_loaded)
            {
                if (pInputManager.IsPressed(Input.Shoot) && _spaceCouldBePressed)
                {
                    _spaceCouldBePressed = false;
                    _playerShot.Play();
                    _loaded = false;
                    ShotSprite.IsFlying = true;
                    Texture = _textureUnloaded;
                    Position = new Vector2(Position.X, Position.Y + 13);
                }   
            }
            else
            {
                OutOfScreen = ShotSprite.Position.Y < -ShotSprite.Texture.Height;
                if (OutOfScreen || GotEnemy)
                {
                    _loaded = true;
                    ShotSprite.IsFlying = false;
                    Texture = _textureLoaded;
                    Position = new Vector2(Position.X, Position.Y - 13);
                    GotEnemy = false;
                }
            }

            PositionBox = new Rectangle((int) Position.X, (int) Position.Y, 
                (int) (_textureUnloaded.Width * 1.3f),(int) (_textureUnloaded.Height * 1.3f));
        }

        public override void Draw(SpriteBatch pSpriteBatch, float pScale = 1)
        {
            base.Draw(pSpriteBatch, pScale);
            ShotSprite.Draw(pSpriteBatch, pScale);
        }
    }
}