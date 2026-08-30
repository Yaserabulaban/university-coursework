function [statistics, car_Interval] = simulateCars(Number_Of_Cars, interArrival_Data, washBay1_data, washBay2_data, washBay3_data, serviceTypes_Data, rule_choice)
    % Initialize the next available time for each wash bay
    nextAvailableTime = zeros(1, 3);

    % Define specializations for each wash bay
    washBaySpecializations = {'Washing', 'Polishing', 'Waxing'};

    % Store all events in an array and initialize statistics storage
    events = {};
    statistics = cell(3, 1);
    for j = 1:3
        statistics{j} = {};
    end

    % Generate inter-arrival times and assign cars to wash bays and service types
    car_Interval = zeros(1, Number_Of_Cars);
    for count = 1:Number_Of_Cars
        carRandInterval = generateRandomInt(1, 100);  % Generate integer between 1 and 100
        if count == 1
            car_Interval(count) = 0;
        else
            car_Interval(count) = getTimeFromRange(carRandInterval, interArrival_Data);
        end

        % Assign a random service type
        randServiceType = generateRandomInt(1, 100);
        serviceType = getServiceType(randServiceType, serviceTypes_Data);

        % Assign cars to the corresponding wash bay based on rule
        switch rule_choice
            case 1
                % Rule 1: Assign car to the wash bay with the specialization
                bay = find(strcmp(washBaySpecializations, serviceType), 1);
            case 2
                % Rule 2: Find the idle wash bay or default to wash bay 1 if all are idle
                [minTime, bay] = min(nextAvailableTime);
            otherwise
                error('Invalid rule choice. Please choose 1 or 2.');
        end

        % Determine the service time and the actual start time of the service
        serviceTime = getServiceTime(randServiceType, eval(['washBay' num2str(bay) '_data']));
        arrivalTime = sum(car_Interval(1:count));
        startTime = max(arrivalTime, nextAvailableTime(bay));
        endTime = startTime + serviceTime;
        waitingTime = startTime - arrivalTime;
        timeInSystem = waitingTime + serviceTime;

        % Update the next available time for the wash bay
        nextAvailableTime(bay) = endTime;

        % Store the arrival and service events in the array
        events = [events; {arrivalTime, 'Arrival', count, bay, startTime, endTime}];

        % Store the statistics for this car in the current wash bay
        statistics{bay} = [statistics{bay}; {count, randServiceType, arrivalTime, serviceTime, startTime, endTime, waitingTime, timeInSystem, serviceType}];
    end

    % Find the maximum end time manually
    maxTime = 0;
    for i = 1:size(events, 1)
        if events{i, 6} > maxTime
            maxTime = events{i, 6};
        end
    end

    % Simulate the process by iterating through the clock and checking events
    for clock = 0:maxTime
        for i = 1:size(events, 1)
            arrivalTime = events{i, 1};
            carID = events{i, 3};
            bay = events{i, 4};
            startTime = events{i, 5};
            endTime = events{i, 6};

            if arrivalTime == clock
                fprintf('Arrival of car %d at %s, Service for car %d started at %s in wash bay %d\n', ...
                    carID, convertTime(arrivalTime), carID, convertTime(startTime), bay);
            end
            if endTime == clock
                fprintf('Service for car %d ended at %s in wash bay %d\n', carID, convertTime(endTime), bay);
            end
        end
    end

    % Print the statistics tables
    printStatisticsTables(statistics);
end

function timeString = convertTime(minutes)
    % Function to convert minutes to hours and minutes string
    hours = floor(minutes / 60);
    minutes_remaining = mod(minutes, 60);
    timeString = sprintf('%d hours %d minutes', hours, minutes_remaining);
end

function printStatisticsTables(statistics)
    for j = 1:3
        fprintf('\n\n');
        fprintf('========================================== W A S H  B A Y  %d =======================================\n', j);
        fprintf('%-4s %-12s %-8s %-11s %-18s %-16s %-12s %-21s %-10s\n', 'n', 'RN for', 'Arrival', 'Service', 'Time service', 'Time service', 'Waiting', 'Time spends in', 'Service');
        fprintf('%-4s %-12s %-8s %-11s %-18s %-16s %-12s %-21s %-10s\n', '', 'service time', 'time', 'time', 'begins', 'ends', 'time', 'the system', 'Type');
        for i = 1:size(statistics{j}, 1)
            fprintf('%-4d %-12d %-8d %-11d %-18d %-16d %-12d %-21d %-10s\n', ...
                statistics{j}{i, 1}, statistics{j}{i, 2}, statistics{j}{i, 3}, ...
                statistics{j}{i, 4}, statistics{j}{i, 5}, statistics{j}{i, 6}, ...
                statistics{j}{i, 7}, statistics{j}{i, 8}, statistics{j}{i, 9});
        end
        fprintf('\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n');
        fprintf('Total cars served by WashBay %d: %d\n', j, size(statistics{j}, 1));
        fprintf('>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n\n');
    end
end
