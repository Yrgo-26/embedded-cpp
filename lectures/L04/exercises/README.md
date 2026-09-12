# L04 Övningar - Din arbetskatalog

Skriv dina lösningar till övningarna i kursboken, §1.4 *Exercises*, här, en katalog per
övningsset och med filnamnen nedan. Det är allt som behövs för att `make test` ska hitta dem:

```text
lectures/L04/exercises/
    exercise1/main.cpp            Övningsset 1: debug::log och app::delay_ms
    exercise2/driver/timer.hpp    Övningsset 2: mjukvarutimern
    exercise2/main.cpp                          och programmet som använder den
    exercise3/main.cpp            Övningsset 3: swap
    exercise4/main.cpp            Övningsset 4: templaten clear och toggle
    test/                         Testsviten. Denna redigerar du inte.
```

Bygg och kör varje program med en egen Makefile, enligt
kursboken, §1.1 *Simple Makefile*. Kör därefter, från repots rot:

```bash
make test               # Samtliga lektioners testsviter, mot din kod.
```

eller från `lectures/L04/exercises/test`, för enbart denna lektion:

```bash
make                    # Denna lektions testsvit, mot din kod.
make SOLUTIONS=1        # Samma tester, mot lösningsförslagen.
```

Ett set du inte har börjat på rapporteras som `SKIP`, tillsammans med den fil testerna väntar på. Så
snart filen finns byggs och körs dess tester; det finns ingenting att registrera.

**Ditt arbete här committas inte.** Repots `.gitignore` ignorerar allt i denna katalog utom denna
README och `test/`, så `git status` hålls tyst och en `git pull` av nytt kursmaterial kolliderar
aldrig med dina filer. Använd `git add -f` för en fil du ändå vill committa.

Lösningsförslagen finns i [`appendix/solutions`](../appendix/solutions/README.md). Försök med varje
övning innan du läser dem.
