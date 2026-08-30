function evaluateResults(car_Interval, car_Counters)
    total_waiting_time = 0;
    total_service_time = 0;
    total_time_in_system = 0;
    num_cars = sum(cellfun(@(x) size(x, 1), car_Counters));
    cars_waiting = 0;

    for i = 1:3
        for j = 1:size(car_Counters{i}, 1)
            carID = car_Counters{i}{j, 1};
            service_start_time = car_Counters{i}{j, 3};
            service_time = car_Counters{i}{j, 2};
            arrival_time = car_Interval(carID);
            waiting_time = service_start_time - arrival_time;
            time_in_system = waiting_time + service_time;

            total_waiting_time = total_waiting_time + waiting_time;
            total_service_time = total_service_time + service_time;
            total_time_in_system = total_time_in_system + time_in_system;

            if waiting_time > 0
                cars_waiting = cars_waiting + 1;
            end
        end
    end

    avg_waiting_time = total_waiting_time / num_cars;
    avg_service_time = total_service_time / num_cars;
    avg_time_in_system = total_time_in_system / num_cars;
    prob_waiting = cars_waiting / num_cars;

    fprintf('Average Waiting Time: %.2f minutes\n', avg_waiting_time);
    fprintf('Average Service Time: %.2f minutes\n', avg_service_time);
    fprintf('Average Time in System: %.2f minutes\n', avg_time_in_system);
    fprintf('Probability of Waiting: %.2f\n', prob_waiting);
end
