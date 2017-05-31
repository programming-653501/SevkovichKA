using System.Collections.Generic;
using System.IO;
using Microsoft.Xna.Framework.Audio;
using Microsoft.Xna.Framework.Graphics;

namespace GalaxianGame
{
    public static class ContentManager
    {
        public static Texture2D GetTexture2D(GraphicsDevice pGraphicsDevice, string pPathToFile)
        {
            if (!File.Exists(pPathToFile))
                throw new FileNotFoundException("File " + pPathToFile + " not found!");

            var texture2D = Texture2D.FromStream(pGraphicsDevice, File.OpenRead(pPathToFile));
       
            return texture2D;
        }

        public static SoundEffect GetSoundEffect(string pPathToFile)
        {

            if (!File.Exists(pPathToFile))
                throw new FileNotFoundException("File " + pPathToFile + " not found!");

            var soundEffect  = SoundEffect.FromStream(File.OpenRead(pPathToFile));

            return soundEffect;
        }

        public static Dictionary<char, int> GetFontMapping(string pPathToFile)
        {
            if (!File.Exists(pPathToFile))
                throw new FileNotFoundException("File " + pPathToFile + " not found!");

            string[] lines;
            using (var sr = new StreamReader(pPathToFile))
            {
                var dataFromfile = sr.ReadToEnd();
                lines = dataFromfile.Split('\n');
            }

            var fontMapping = new Dictionary<char, int>();
            foreach (var str in lines)
            {
                var line = str.Split('|');
                var key = line[0].ToCharArray()[0];
                var value = int.Parse(line[1]);
                fontMapping.Add(key, value);
            }

            return fontMapping;
        }
    }
}
