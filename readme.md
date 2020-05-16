## COVID 19 GRAPHICAL SPREAD SIMULATOR

### WIP Sample

![Sample WIP Output](https://github.com/TonyJosi97/covid19_spread_simulator/blob/master/cvdssim_wip_sample_1.gif)

### BASIC BRIEF DESIGN:

### Init func
* init cvd19ssim_core_t from file or #defs from a new header or static constructor call
* initial population count is between max popl and (max popl. - INIT_POPL_LOWER_LIMIT_DIFF)
    * init max_allowed_population_in_city
    * init total_population with this val
* initialise initial popl
    * alloc mem
    * init each entities cvd19ssim_entity_mvmnt_t pos with random val b/w city size
    init each entities cvd19ssim_entity_mvmnt_t accel within a range b/w MAX_ACCELERATION & MIN_ACCELERATION
    * assign all cvd19ssim_core_covid_entity_report_t with zeroes
    * assign is_alive true
    * assign prob_early_death & prob_better_immunity based on min and max from core data


### Main Loop
* **while(1)**

    * new normal deaths
        * normal death for non infected persons
        * loop through non covid & recvered & alive
            * death is functions of global death rate, immunity, prob_early_death & random selection
                * mark is_alive false
        * update cur_population

    * covid deaths
        * loop through covid infected & alive
            * function of low immunity, whether hospitalised or not, days of infections (> 28 days) and randomness
                * mark is_alive false
                * if death was from hospital
                    * decrease from cur_filled_hosp_capacity
        * update cur_population, total_infected_n_died

    * new births
       *  should be less than max. popl. limit
            * based on randomness and birth rate
                * loop from beginning of the entities
                * mark the first non_alive as alive
                * update total_population with new births
            * update cur_population

    * movement
        * loop through all non hospitalised & alive
            * movment based on acceleration and random sign for movemnt (forward and backward in (x, y))

    * new infections
        * loop through all non infected (recovered not included) & alive
            * infection is a func. of if inside max_spread_distance and immunity and randomness

    * diagnosis
        * loop through all people with symptoms and test random numbers and alive
            * no. of tests done should be in the range [noof. with symptoms, max tests available]
            * update total_infected

    * hospitalization
        * if cur_filled_hosp_capacity < num_of_hospitals_in_city * capacity_per_hospital
            * all +ve tests subjects are hospitalized
        * else 
            * avail. part of all +ve tests subjects are hospitalized
        * increment cur_filled_hosp_capacity by +ve cases admitted


    * recovery
        * loop through all infected & alive
            * recovery is a function of immunity and days of infection (< 14 days)
                * if recovry was from hospital
                    * decrease from cur_filled_hosp_capacity
            * update total_recovered

    * `cvd19ssim_daily_summary_calc`
        * inc days_passed
        * inf days for infected people
        * (new feature) add age for each entity (incorporate that in all algos)



### misc. data:
* death rate needs to be equal to death rate?
* acceleration in both x, y should be 1 unit for better visual rep (only sign changes)

### TO DO:
* INCREMENT INF DAYS (each day), increment new births, new deaths
* log report of each day to a file
* when births reached max pop count and all people are healthy (ie no deaths) birth and death
  becomes stagnant. 
* hb people infected with cvd in hospitals (in map?)
* when deaths make is_alive false
    * decrement cur_population
* when births loop from beginning, make one alive, reset the struct feilds, if no dead found init new
    * increment cur_population

### Build & Run:

`make`

`./cvd19ssim | mpv --no-correct-pts --fps=5 -`

### Rough Works:


#### cvd19ssim_covid_infections()

    // loop through all infected & not hospitalised (quarantined)

        // increment days of infection

        // calc people who will get infected
        
            // distance
        
            // immunity
        
            // recovered?
        
        // insert newly infected ID in local array
    
    // after looping init IDs in array into struct
    
        // add data abt symtoms
    
        // days of infections 