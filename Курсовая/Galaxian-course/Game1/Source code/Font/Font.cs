using System;
using System.Collections.Generic;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;

namespace GalaxianGame
{
    public class Font
    {
        private readonly CelledSprite _framedSprite;
        private readonly Dictionary<char, int> _mapping;

        public Font(CelledSprite pFramedSprite, Dictionary<char, int> pMapping)
        {
            _framedSprite = pFramedSprite;
            _mapping = pMapping;
        }

        public void DrawString(SpriteBatch pSpriteBatch, string pText, Vector2 pPosition, float pScale = 1f)
        {
            var x = Convert.ToInt32(pPosition.X);

            foreach (var symbol in pText)
            {
                if (_mapping.ContainsKey(symbol))
                {
                    var cellNumber = _mapping[symbol];
                    _framedSprite.Draw(pSpriteBatch, new Vector2(x, pPosition.Y), cellNumber, pScale);
                    x += Convert.ToInt32(pScale * _framedSprite.CellSize.Width);
                }
            }
        }
    }
}
