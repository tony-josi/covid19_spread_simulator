// pseudo code

// main driver
/*


while(1)

    new deaths
        total popl. greater than min popl.
        death for non infected persons
        loop through non covid & recvered 
            death is functions of global death rate, immunity, prob_early_death & random selection
                mark is_alive false

    covid deaths
        loop through covid infected
            function of low immunity, whether hospitalised or not, days of infections (> 28 days) and randomness
                mark is_alive false
                if death was from hospital
                    decrease from cur_filled_hosp_capacity

    new births
        should be less than max. popl. limit
        based on randomness and birth rate
            loop from beginning of the entities
            mark the first non_alive as alive

    movement
        loop through all non hospitalised
        movment based on acceleration and random sign for movemnt (forward and backward in (x, y))

    new infections
        loop through all non infected (recovered not included)
        infection is a func. of min. spread distance and immunity and randomness

    diagnosis
        loop through all people with symptoms and test random numbers
        no. of tests done should be in the range [noof. with symptoms, max tests available]

    hospitalization
        if cur_filled_hosp_capacity < num_of_hospitals_in_city * capacity_per_hospital
            all +ve tests subjects are hospitalized
        else 
            avail. part of all +ve tests subjects are hospitalized
        increment cur_filled_hosp_capacity by +ve cases admitted


    recovery
        loop through all infected
        recovery is a function of immunity and days of infection (< 14 days)
            if recovry was from hospital
                decrease from cur_filled_hosp_capacity

*/
