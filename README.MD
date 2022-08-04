# Template de setup Xoverse
Ceci est un template de setup basique.
## Comment �a marche ?
Un fichier ZIP est compress� dans l'application.

Lors de l'installation, ce fichier ZIP est copi� dans le dossier temporaire de l'utilisateur.

Une fois copi�, il est d�compress� dans le dossier choisi.
## L'utiliser pour son application
1. Compresser son application en .ZIP (avec WinRar, 7-zip, etc...)
2. Replacer le `app.zip` avec le votre (le nom est important)
3. Remplacez le nom de l'application dans `Config.h` comme ceci:<br>
    `Ligne 14`
    ```cpp
    static String^ GameName = "Nom Du Jeu"; // The name of your game
    ```
4. (Optionnel) Remplacez la couleur de la barre du haut dans `Config.h` comme ceci:<br>
    `Ligne 15`
    ```cpp
    static Color BarColor = Color::FromArgb(0-255, 0-255, 0-255); // The top bar color
    ```
5. Compilez avec le `build.bat`, msbuild ou Visual Studio (outils v142/2019)
## Preview
[Build du template](https://github.com/Xoverse/Setup/releases/latest)
![preview image](https://i.imgur.com/NJJnEDw.png)