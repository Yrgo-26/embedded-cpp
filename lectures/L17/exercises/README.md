# L17 Övningar - Din arbetskatalog

Skriv dina lösningar till övningarna i kursboken, §6.3 *Exercises*, här, en katalog per
övningsset och med filnamnen nedan. Det är allt som behövs för att `make test` ska hitta dem:

```text
lectures/L17/exercises/
    exercise1/exercise1.cpp       Övningsset 1: workerThread och en atomisk stoppflagga
    exercise2/exercise2.cpp       Övningsset 2: incrementCounter och en delad räknare
    exercise3/exercise3.cpp       Övningsset 3: SharedMem, txThread och rxThread
    exercise4-5/                  Övningsset 4 och 5: den trådsäkra stub-räknaren
        include/driver/counter/interface.hpp
        include/driver/counter/stub.hpp
        source/main.cpp
    exercise6/exercise6.cpp       Övningsset 6: versionen av set 3 med condition variable
    exercise7/exercise7.cpp       Övningsset 7: validateFirmware och std::async
    test/                         Testsviten. Denna redigerar du inte.
```

Bygg och kör varje program med en egen Makefile, enligt
kursboken, §1.1 *Simple Makefile*, med `-pthread` tillagt i
kompilatorflaggorna. Kör därefter, från repots rot:

```bash
make test               # Samtliga lektioners testsviter, mot din kod.
```

eller från `lectures/L17/exercises/test`, för enbart denna lektion:

```bash
make                    # Denna lektions testsvit, mot din kod.
make SOLUTIONS=1        # Samma tester, mot lösningsförslagen.
```

Ett set du inte har börjat på rapporteras som `SKIP`, tillsammans med den fil testerna väntar på. Så
snart filen finns byggs och körs dess tester; det finns ingenting att registrera.

**Varje fil växer genom sitt set, och testerna kontrollerar var den landar**: stoppflaggan i Övning
1.3, den atomiska räknaren i Övning 2.3, initialiseringsflaggan i övningsset 5. Innan du har nått
slutet av ett set, förvänta dig att dess tester misslyckas att kompilera eller rapporterar vad som
fortfarande saknas.

**Ditt arbete här committas inte.** Repots `.gitignore` ignorerar allt i denna katalog utom denna
README och `test/`, så `git status` hålls tyst och en `git pull` av nytt kursmaterial kolliderar
aldrig med dina filer. Använd `git add -f` för en fil du ändå vill committa.

Lösningsförslagen finns i [`appendix/solutions`](../appendix/solutions/README.md). Försök med varje
övning innan du läser dem.
