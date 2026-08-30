function Main()
    displayTitle();
    
    % User inputs the number of cars
    valid = 0;
    Number_Of_Cars = input('Enter Number Of Cars: ');
    while (valid == 0)
        if (Number_Of_Cars < 1)
            fprintf('There Should Be At Least 1 Car To Run The Simulation\n');
            Number_Of_Cars = input('Enter Number Of Cars: ');
        else
            valid = 1;
        end
    end

    % User selects the random number generator type
    rng_type = selectRNGType();

    % Generate tables for service times and inter-arrival times
    [washBay1_data, washBay2_data, washBay3_data] = generateServiceTimeTables(rng_type);
    interArrival_Data = generateInterArrivalTimeTable(rng_type);

    % Initialize interarrival times based on probabilities
    car_Interval = zeros(1, Number_Of_Cars);

    % Initialize counter-specific car arrays
    car_Counter1 = [];
    car_Counter2 = [];
    car_Counter3 = [];

    % Generating interarrival times and assigning cars to counters
    for count = 1:Number_Of_Cars
        carRandInterval = randi([1, 100]);  % Generate integer between 1 and 100
        if count == 1
            car_Interval(count) = 0;
        else
            car_Interval(count) = getTimeFromRange(carRandInterval, interArrival_Data);
        end
        
        % Assign cars to the corresponding counter
        switch mod(count, 3)
            case 1
                car_Counter1 = [car_Counter1; count, getServiceTime(randi([1, 100]), washBay1_data), car_Interval(count)];
            case 2
                car_Counter2 = [car_Counter2; count, getServiceTime(randi([1, 100]), washBay2_data), car_Interval(count)];
            case 0
                car_Counter3 = [car_Counter3; count, getServiceTime(randi([1, 100]), washBay3_data), car_Interval(count)];
        end
    end

    % Display car information table for each counter
    fprintf('****************Counter 1****************:\n');
    displayTable(car_Counter1);

    fprintf('****************Counter 2****************:\n');
    displayTable(car_Counter2);

    fprintf('****************Counter 3 ****************:\n');
    displayTable(car_Counter3);

    % Simulate car arrivals and services
    simulateCars(Number_Of_Cars, car_Interval, {car_Counter1, car_Counter2, car_Counter3});

    % Evaluate and display results
    evaluateResults(car_Interval, {car_Counter1, car_Counter2, car_Counter3});
end
