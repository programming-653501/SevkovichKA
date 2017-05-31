using System;
using System.Collections.Generic;
using Microsoft.Xna.Framework.Input;

namespace GalaxianGame
{
    public class InputManager
    {
        private readonly Dictionary<Keys, Input> _inputDictionary;
        private int _playersInput;

        public InputManager()
        {
            _inputDictionary = new Dictionary<Keys, Input>
            {
                { Keys.Left  , Input.MoveLeft  },
                { Keys.Right , Input.MoveRight },
                { Keys.Up    , Input.MoveUp    },
                { Keys.Down  , Input.MoveDown  },
                { Keys.Space , Input.Shoot     },
                { Keys.Escape, Input.Escape    },
                { Keys.Enter , Input.Enter     }
            };
        }

        public void Update()
        {
            _playersInput = 0;

            var pressedKeys = Keyboard.GetState().GetPressedKeys();

            foreach (var key in pressedKeys)
            {
                if (_inputDictionary.ContainsKey(key))
                    _playersInput |= Convert.ToInt32(_inputDictionary[key]);
            }
        }

        public bool IsPressed(params Input[] inpunts)
        {
            int n = 0;

            foreach (var input in inpunts)
            {
                n |= Convert.ToInt32(input);
            }

            return (_playersInput & n) == n;
        }
    }
}