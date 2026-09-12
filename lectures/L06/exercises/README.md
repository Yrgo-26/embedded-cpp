# L06 Övningar - Din arbetskatalog

Skriv din lösning till övningsset 4 *Timer Class* i kursboken, §2.4 *Exercises*, här, med filnamnen
nedan. Det är allt som behövs för att `make test` ska hitta den:

```text
lectures/L06/exercises/
    exercise1/include/driver/timer.hpp    Klassen Timer,
    exercise1/source/driver/timer.cpp     uppdelad på två filer,
    exercise1/source/main.cpp             och programmet som testar den
    test/                                 Testsviten. Denna redigerar du inte.
```

De ytterligare övningsuppgifterna i [Bilaga B](../appendix/b_exercises.md) - en riktig GPIO-driver
för ATmega328P - finns inte i boken, byggs för AVR i Microchip Studio och testas därför inte av
sviten. De har ett eget lösningsförslag.

Bygg och kör programmet med en egen Makefile, enligt
kursboken, §1.1 *Embedded project structure*. Kör därefter, från
repots rot:

```bash
make test               # Samtliga lektioners testsviter, mot din kod.
```

eller från `lectures/L06/exercises/test`, för enbart denna lektion:

```bash
make                    # Denna lektions testsvit, mot din kod.
make SOLUTIONS=1        # Samma tester, mot lösningsförslaget.
```

Så länge du inte har börjat rapporteras övningen som `SKIP`, tillsammans med den fil testerna väntar
på.

**Ditt arbete här committas inte.** Repots `.gitignore` ignorerar allt i denna katalog utom denna
README och `test/`, så `git status` hålls tyst och en `git pull` av nytt kursmaterial kolliderar
aldrig med dina filer. Använd `git add -f` för en fil du ändå vill committa.

Lösningsförslagen finns i [`appendix/solutions`](../appendix/solutions/README.md). Försök med
övningen innan du läser dem.
