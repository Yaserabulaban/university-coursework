function simulateCars(Number_Of_Cars, car_Interval, car_WashBays)
    % Function to simulate car arrivals and services
    % Inputs:
    %   Number_Of_Cars - total number of cars
    %   car_Interval - array of inter-arrival times for each car
    %   car_WashBays - cell array containing car data for each wash bay

    % Initialize the next available time for each wash bay
    nextAvailableTime = zeros(1, 3);

    for i = 1:Number_Of_Cars
        % Print arrival message
        fprintf('Arrival of car %d at minute %d\n', i, car_Interval(i));

        % Iterate through each wash bay to check service times
        for j = 1:3
            if i <= size(car_WashBays{j}, 1)
                carID = car_WashBays{j}{i, 1};
                serviceTime = car_WashBays{j}{i, 2};
                arrivalTime = car_Interval(i);

                % Determine the actual start time of the service
                startTime = max(arrivalTime, nextAvailableTime(j));
                endTime = startTime + serviceTime;

                % Update the next available time for the wash bay
                nextAvailableTime(j) = endTime;

                % Print service start and end messages
                fprintf('Service for car %d started at minute %d in wash bay %d\n', carID, startTime, j);
                fprintf('Service for car %d ended at minute %d in wash bay %d\n', carID, endTime, j);
            end
        end
    end
end
