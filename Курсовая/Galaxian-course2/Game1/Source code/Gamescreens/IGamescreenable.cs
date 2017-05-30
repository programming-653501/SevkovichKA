using Microsoft.Xna.Framework;

namespace GalaxianGame
{
    public interface IGamescreenable
    {
        void LoadContent();
        void Update(GameTime pGameTime);
        void Draw(GameTime pGameTime);
    }
}
