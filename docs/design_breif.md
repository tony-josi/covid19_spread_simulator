
### BASIC BRIEF DESIGN:

### Init func
* Init cvd19ssim_core_t from file or #defs from a new header or static constructor call
* Initial population count is between max popl and (max popl. - INIT_POPL_LOWER_LIMIT_DIFF)
    * Init max_allowed_population_in_city
    * Init total_population with this val
* Initialise initial popl
    * Alloc mem
    * Init each entities cvd19ssim_entity_mvmnt_t pos with random val b/w city size
    init each entities cvd19ssim_entity_mvmnt_t accel within a range b/w MAX_ACCELERATION & MIN_ACCELERATION
    * Assign all cvd19ssim_core_covid_entity_report_t with zeroes
    * Assign is_alive true
    * Assign prob_early_death & prob_better_immunity based on min and max from core data


### Main Loop
* **while(1):**

    * New normal deaths
        * Normal death for non infected persons
        * Loop through non covid & recvered & alive
            * Death is functions of global death rate, immunity, prob_early_death & random selection
                * Mark is_alive false
        * Update cur_population

    * Covid deaths
        * Loop through covid infected & alive
            * Function of low immunity, whether hospitalised or not, days of infections (> 28 days) and randomness
                * Mark is_alive false
                * If death was from hospital
                    * Decrease from cur_filled_hosp_capacity
        * Update cur_population, total_infected_n_died

    * New births
       * Should be less than max. popl. limit
            * Based on randomness and birth rate
                * Loop from beginning of the entities
                * Mark the first non_alive as alive
                * Update total_population with new births
            * Update cur_population

    * Movement
        * Loop through all non hospitalised & alive
            * Movment based on acceleration and random sign for movemnt (forward and backward in (x, y))

    * New infections
        * Loop through all non infected (recovered not included) & alive
            * Infection is a func. of if inside max_spread_distance and immunity and randomness

    * Diagnosis
        * Loop through all people with symptoms and test random numbers and alive
            * No. of tests done should be in the range [noof. with symptoms, max tests available]
            * Update total_infected

        * Hospitalization
            * If cur_filled_hosp_capacity < num_of_hospitals_in_city * Capacity_per_hospital
                * All +ve tests subjects are hospitalized
            * Else 
                * Avail. part of all +ve tests subjects are hospitalized
            * Increment cur_filled_hosp_capacity by +ve cases admitted


    * Recovery
        * Loop through all infected & alive
            * Recovery is a function of immunity and days of infection (< 14 days)
                * If recovry was from hospital
                    * Decrease from cur_filled_hosp_capacity
            * Update total_recovered

    * `cvd19ssim_daily_summary_calc`
        * Inc days_passed
        * Inf days for infected people
        * (new feature) add age for each entity (incorporate that in all algos)



### misc. data:
* Death rate needs to be equal to death rate?
* Acceleration in both x, y should be 1 unit for better visual rep (only sign changes)

### TO DO:
* INCREMENT INF DAYS (each day), increment new births, new deaths
* Log report of each day to a file
* When births reached max pop count and all people are healthy (ie no deaths) birth and death
  becomes stagnant. 
* Hb people infected with cvd in hospitals (in map?)
* When deaths make is_alive false
    * Decrement cur_population
* When births loop from beginning, make one alive, reset the struct feilds, if no dead found init new
    * Increment cur_population

### Rough Works:

#### cvd19ssim_covid_infections()

```    
    loop through all infected & not hospitalised (quarantined)
        increment days of infection
        calc people who will get infected
            distance
            immunity
            recovered
        insert newly infected ID in local array
    after looping init IDs in array into struct
        add data abt symtoms
        days of infections 
```