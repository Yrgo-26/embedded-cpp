# L14 Övningar - Din arbetskatalog

Skriv din lösning till övningarna i kursboken, §4.4 *Exercises*, övningsset 4, här. Börja med att kopiera
din färdiga `raw_factory` från [`lectures/L13/exercises`](../../L13/exercises/README.md) till
`smart_factory` här, och gör därefter om den till `std::unique_ptr`:

```bash
cp -r ../../L13/exercises/raw_factory smart_factory
```

Strukturen är densamma som i L13:

```text
lectures/L14/exercises/
    smart_factory/                        En kopia av raw_factory, därefter uppdaterad
        include/
            app/logic/logic.hpp           Övning 1.3: en std::unique_ptr-medlem, ingen destruktor
            driver/factory/interface.hpp  Övning 1.1: serial() returnerar std::unique_ptr
            driver/factory/esp32s3.hpp    Övning 1.2: std::make_unique
            driver/factory/stub.hpp       Övning 1.2: std::make_unique
            driver/serial/interface.hpp   Oförändrade från L13
            driver/serial/esp32s3.hpp
            driver/serial/stub.hpp
        source/main.cpp
    test/                                 Testsviten. Denna redigerar du inte.
```

Att arbeta i en kopia är avsiktligt: den gamla versionen med råa pekare finns kvar i L13 att jämföra
med.

Bygg och kör programmet med en egen Makefile, enligt
kursboken, §1.1 *Embedded project structure*. Kör därefter, från
repots rot:

```bash
make test               # Samtliga lektioners testsviter, mot din kod.
```

eller från `lectures/L14/exercises/test`, för enbart denna lektion:

```bash
make                    # Denna lektions testsvit, mot din kod.
make SOLUTIONS=1        # Samma tester, mot lösningsförslaget.
```

Testerna slås på fil för fil: de börjar med det nya factory-interfacet och plockar upp factories och
logikklassen i takt med att du uppdaterar dem. Innan du har börjat rapporteras setet som `SKIP`.

**Ditt arbete här committas inte.** Repots `.gitignore` ignorerar allt i denna katalog utom denna
README och `test/`, så `git status` hålls tyst och en `git pull` av nytt kursmaterial kolliderar
aldrig med dina filer. Använd `git add -f` för en fil du ändå vill committa.

Lösningsförslaget finns i [`appendix/solutions`](../appendix/solutions/README.md). Försök med varje
övning innan du läser det.
