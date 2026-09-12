# L05 Övningar - Din arbetskatalog

Skriv dina lösningar till övningarna i kursboken, §2.4 *Exercises*, övningsset 1-3, här, en katalog per
övningsset och med filnamnen nedan. Det är allt som behövs för att `make test` ska hitta dem:

```text
lectures/L05/exercises/
    exercise1/include/driver/gpio/led.hpp       Övningsset 1: klassen Led
    exercise1/include/driver/gpio/button.hpp                  klassen Button
    exercise1/main.cpp                                        och programmet som använder båda
    exercise2/include/driver/gpio/led.hpp       Övningsset 2: samma klasser,
    exercise2/include/driver/gpio/button.hpp
    exercise2/main.cpp                                        styrda av en knapp och blinkande
    exercise3/include/driver/buzzer.hpp         Övningsset 3: klassen Buzzer,
    exercise3/source/driver/buzzer.cpp                        uppdelad på två filer,
    exercise3/source/main.cpp                                 och programmet som använder den
    test/                                       Testsviten. Denna redigerar du inte.
```

Bygg och kör varje program med en egen Makefile: den i
kursboken, §1.1 *Simple Makefile*, för övningsset 1 och 2, med
`-Iinclude` tillagt i kompilatorflaggorna, och den för en
kursboken, §1.1 *Embedded project structure* för
övningsset 3. Kör därefter, från repots rot:

```bash
make test               # Samtliga lektioners testsviter, mot din kod.
```

eller från `lectures/L05/exercises/test`, för enbart denna lektion:

```bash
make                    # Denna lektions testsvit, mot din kod.
make SOLUTIONS=1        # Samma tester, mot lösningsförslagen.
```

Ett set du inte har börjat på rapporteras som `SKIP`, tillsammans med den fil testerna väntar på. Så
snart filen finns byggs och körs dess tester; det finns ingenting att registrera. Övningsset 1 testas
så snart `led.hpp` finns, testerna för `Button` ansluter när `button.hpp` gör det, och programmets
utskrift kontrolleras när `main.cpp` finns.

**Ditt arbete här committas inte.** Repots `.gitignore` ignorerar allt i denna katalog utom denna
README och `test/`, så `git status` hålls tyst och en `git pull` av nytt kursmaterial kolliderar
aldrig med dina filer. Använd `git add -f` för en fil du ändå vill committa.

Lösningsförslagen finns i [`appendix/solutions`](../appendix/solutions/README.md). Försök med varje
övning innan du läser dem.
