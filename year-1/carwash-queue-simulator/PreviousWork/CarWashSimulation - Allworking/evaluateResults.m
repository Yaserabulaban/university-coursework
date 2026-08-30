function results = evaluateResults(statistics, car_Interval)
    % Function to evaluate and print the results of the simulation
    total_waiting_time = 0;
    total_service_time = 0;
    total_time_in_system = 0;
    num_cars = 0;
    total_arrival_time = 0;
    total_interarrival_time = sum(car_Interval);
    cars_waiting = 0;

    for j = 1:3
        num_cars = num_cars + size(statistics{j}, 1);
        for i = 1:size(statistics{j}, 1)
            waiting_time = statistics{j}{i, 6};
            service_time = statistics{j}{i, 3};
            time_in_system = statistics{j}{i, 7};
            arrival_time = sum(car_Interval(1:statistics{j}{i, 1}));

            total_waiting_time = total_waiting_time + waiting_time;
            total_service_time = total_service_time + service_time;
            total_time_in_system = total_time_in_system + time_in_system;
            total_arrival_time = total_arrival_time + arrival_time;

            if waiting_time > 0
                cars_waiting = cars_waiting + 1;
            end
        end
    end

    avg_waiting_time = total_waiting_time / num_cars;
    avg_service_time = total_service_time / num_cars;
    avg_time_in_system = total_time_in_system / num_cars;
    avg_arrival_time = total_arrival_time / num_cars;
    avg_interarrival_time = total_interarrival_time / (num_cars - 1);
    prob_waiting = cars_waiting / num_cars;

    results = struct();
    results.avg_waiting_time = avg_waiting_time;
    results.avg_service_time = avg_service_time;
    results.avg_time_in_system = avg_time_in_system;
    results.avg_arrival_time = avg_arrival_time;
    results.avg_interarrival_time = avg_interarrival_time;
    results.prob_waiting = prob_waiting;
end
