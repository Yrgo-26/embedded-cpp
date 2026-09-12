# L16 Övningar - Din arbetskatalog

Skriv din lösning till övningarna i kursboken, §5.5 *Exercises*, övningsset 3, här, med filnamnen nedan.
Det är allt som behövs för att `make test` ska hitta den:

```text
lectures/L16/exercises/
    class_template/include/driver/timer/timer.hpp   Övningsset 1: klasstemplaten Timer
    class_template/source/main.cpp                                och programmet som testar den
    test/                                           Testsviten. Denna redigerar du inte.
```

Övning 1.2 är frågor som besvaras i text, så det finns ingenting att skriva här för den.

Bygg och kör programmet med en egen Makefile, enligt
kursboken, §1.1 *Embedded project structure*. Kör därefter, från
repots rot:

```bash
make test               # Samtliga lektioners testsviter, mot din kod.
```

eller från `lectures/L16/exercises/test`, för enbart denna lektion:

```bash
make                    # Denna lektions testsvit, mot din kod.
make SOLUTIONS=1        # Samma tester, mot lösningsförslaget.
```

Innan du har börjat rapporteras setet som `SKIP`, tillsammans med den fil testerna väntar på. Testet
av programmet slås på när `source/main.cpp` finns.

**Ditt arbete här committas inte.** Repots `.gitignore` ignorerar allt i denna katalog utom denna
README och `test/`, så `git status` hålls tyst och en `git pull` av nytt kursmaterial kolliderar
aldrig med dina filer. Använd `git add -f` för en fil du ändå vill committa.

Lösningsförslaget finns i [`appendix/solutions`](../appendix/solutions/README.md). Försök med varje
övning innan du läser det.
