function simulateCars(Number_Of_Cars, car_Interval, car_Counters)
    current_time = 0;
    car_index = 1;

    while car_index <= Number_Of_Cars
        % Check if the current car is due for arrival
        if current_time == car_Interval(car_index)
            fprintf('Arrival of car %d at minute %d and queue at the counter %d\n', car_index, current_time, mod(car_index-1, 3) + 1);
            car_index = car_index + 1;
        end

        % Check if any car is due for service
        for counter = 1:3
            if ~isempty(car_Counters{counter})
                if car_Counters{counter}(1, 3) == current_time
                    fprintf('Service for car %d started at minute %d at counter %d\n', car_Counters{counter}(1, 1), current_time, counter);
                    endTime = current_time + car_Counters{counter}(1, 2);
                    fprintf('Service for car %d ended at minute %d\n', car_Counters{counter}(1, 1), endTime);
                    car_Counters{counter} = car_Counters{counter}(2:end, :);
                end
            end
        end

        % Increment the current time
        current_time = current_time + 1;
    end
end
