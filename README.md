**Github:**
https://github.com/RvD-Projects/External-CheatEngine

**Dumper:**
https://github.com/a2x/cs2-dumper/releases/download/0.1.2/cs2-dumper.exe

Met le dumper dans le projet github dans `/Engine/GameDumper/` 

Après tu pars le jeu et tu `call` le dumper (ca update les pointeurs offset) 

Après trouve tes bonnes résolutions et met les dans dans: `/Engine/Engine.h L:86` :
```cpp
TargetClient.dimension = Dimension{1920,1080};
```

Après dans visual-studio tu clique sur  `build-release`

Ca va te compiler le **Application.exe** dans: `/Build/Release/`

Ensuite: `call Build\Release\Application.exe`
