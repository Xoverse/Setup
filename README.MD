# Template de setup Xoverse
Ceci est un template de setup basique.
## Informations sur l'utilisation
Nous distribuons gratuitement le logiciel en plus de l'entièreté du code source.
Nous ne prévoyons pas de le rendre payant, donc nous n'avons aucune rentrée d'argent, donc aucun moyen pour nous mettre en avant.
Si vous utilisez ce template, merci de créditer la __Xoverse__. Nous l'apprécierons grandement !
## Comment ça marche ?
Un fichier ZIP est compressé dans l'application.

Lors de l'installation, ce fichier ZIP est copié dans le dossier temporaire de l'utilisateur.

Une fois copié, il est décompressé dans le dossier choisi.
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
[Build du template](https://github.com/Xoverse/Setup/releases/latest)<br>
![preview image](https://i.imgur.com/NJJnEDw.png)
