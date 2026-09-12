# L09 Övningar - Din arbetskatalog

Skriv din lösning till övningarna i kursboken, §3.5 *Exercises*, här. Till skillnad från de
tidigare lektionerna bygger samtliga fyra övningsset **ett** program, så denna katalog *är* det
programmet: katalogstrukturen som §3.5 ber om läggs här, direkt intill denna README och `test/`.
Det är allt som behövs för att `make test` ska hitta den:

```text
lectures/L09/exercises/
    Makefile                              Ditt programs Makefile.
    include/
        driver/
            serial/
                interface.hpp             Övningsset 1: det seriella interfacet
                stub.hpp                  Övningsset 2: stub-drivern
                console.hpp               Övningsset 3: konsoldrivern
    source/
        driver/
            serial/
                stub.cpp                  Övningsset 2
                console.cpp               Övningsset 3
        main.cpp                          Övningsset 4: sendMessage() och programmet
    test/                                 Testsviten. Denna redigerar du inte.
```

Bygg och kör programmet med Makefilen från
kursboken, §1.1 *Embedded project structure*, med de tre
källkodsfilerna listade och `-Iinclude` tillagt i kompilatorflaggorna. Kör därefter, från repots rot:

```bash
make test               # Samtliga lektioners testsviter, mot din kod.
```

eller från `lectures/L09/exercises/test`, för enbart denna lektion:

```bash
make                    # Denna lektions testsvit, mot din kod.
make SOLUTIONS=1        # Samma tester, mot lösningsförslaget.
```

Varje övningsset testas fortfarande för sig, så snart dess filer finns, så du kan kontrollera
interfacet innan du har skrivit en enda driver. Ett set du inte har börjat på rapporteras som `SKIP`,
tillsammans med den fil testerna väntar på.

**Ditt arbete här committas inte.** Repots `.gitignore` ignorerar allt i denna katalog utom denna
README och `test/`, så `git status` hålls tyst och en `git pull` av nytt kursmaterial kolliderar
aldrig med dina filer. Använd `git add -f` för en fil du ändå vill committa.

Lösningsförslaget finns i [`appendix/solutions`](../appendix/solutions/README.md), med exakt samma
struktur som denna katalog. Försök med varje övning innan du läser det.
