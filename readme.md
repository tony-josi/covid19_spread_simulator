## COVID 19 GRAPHICAL SPREAD SIMULATOR

COVID19 SPREAD SIMULATOR is a graphical simulator that simulates the **spread(infections), diagnosis(testing), recovery and death** of entities in a city due to COVID19 along with normal deaths and births of entities happening in the city written in pure **C**. 

The simulator is highly configurable with options to configure limited set of settings using the structure feilds by init functions or building more customized verion by editing private/core define files (such as city size).

#### Basic Design

[Basic control flow](https://github.com/TonyJosi97/covid19_spread_simulator/blob/code_cleanup/docs/design_breif.md)

### WIP Sample

![Sample WIP Output](https://github.com/TonyJosi97/covid19_spread_simulator/blob/master/cvdssim_wip_sample_1.gif)

#### Pixel color coding
* **WHITE**:    White represnets non infected entities
* **BLUE**:     Blue blocks represent hospitals
* **GREEN**:    Green represents COVID recovered entities
* **YELLOW**:   Entities infected and quarantined

### Build & Run:

#### Build

```sh
cd covid19_spread_simulator
make
```

#### Run
``` sh
./cvd19ssim | mpv --no-correct-pts --fps=5 -
```

