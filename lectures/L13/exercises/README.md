# L13 Övningar - Din arbetskatalog

Skriv dina lösningar till övningarna i kursboken, §4.4 *Exercises*, övningsset 1-3, här. Övningsset 1 till 3
bygger ett program med råa pekare, i katalogen `raw_factory`, upplagd som boken ber om. Det är allt
som behövs för att `make test` ska hitta dem:

```text
lectures/L13/exercises/
    raw_factory/                          Övningsset 1 till 3
        include/
            app/logic/logic.hpp           Set 3: app::logic::Logic, som äger en rå pekare
            driver/factory/interface.hpp  Set 2: driver::factory::Interface
            driver/factory/esp32s3.hpp    Set 2: driver::factory::Esp32s3
            driver/factory/stub.hpp       Set 2: driver::factory::Stub
            driver/serial/interface.hpp   Set 1: driver::serial::Interface
            driver/serial/esp32s3.hpp     Set 1: driver::serial::Esp32s3
            driver/serial/stub.hpp        Set 1: driver::serial::Stub
        source/main.cpp                   Set 3: programmet
    test/                                 Testsviten. Denna redigerar du inte.
```

Övningsset 4, där samma program görs om till `std::unique_ptr`, hör till nästa lektion och skrivs i
[`lectures/L14/exercises`](../../L14/exercises/README.md).

Bygg och kör programmet med en egen Makefile, enligt
kursboken, §1.1 *Embedded project structure*. Kör därefter, från
repots rot:

```bash
make test               # Samtliga lektioners testsviter, mot din kod.
```

eller från `lectures/L13/exercises/test`, för enbart denna lektion:

```bash
make                    # Denna lektions testsvit, mot din kod.
make SOLUTIONS=1        # Samma tester, mot lösningsförslaget.
```

Ett övningsset du inte har börjat på rapporteras som `SKIP`, tillsammans med den fil testerna väntar
på. Så snart filen finns byggs och körs dess tester; det finns ingenting att registrera.

**Ditt arbete här committas inte.** Repots `.gitignore` ignorerar allt i denna katalog utom denna
README och `test/`, så `git status` hålls tyst och en `git pull` av nytt kursmaterial kolliderar
aldrig med dina filer. Använd `git add -f` för en fil du ändå vill committa.

Lösningsförslaget finns i [`appendix/solutions`](../appendix/solutions/README.md). Försök med varje
övning innan du läser det.
