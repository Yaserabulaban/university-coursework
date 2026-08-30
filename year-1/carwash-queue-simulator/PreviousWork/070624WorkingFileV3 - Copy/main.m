fprintf('\n-------- Car Wash Simulation --------\n');

% Input the seed value
seed = input('Enter the seed value: ');

% Select the random number generator type
rng_type = selectRNGType();

% Input the number of cars
Number_Of_Cars = input('Enter the number of cars: ');

% Generate tables for service times and inter-arrival times
[washBay1_data, washBay2_data, washBay3_data] = generateServiceTimeTables(rng_type, seed);
interArrival_Data = generateInterArrivalTimeTable(rng_type, seed);

% Print the service time tables
printServiceTimeTable('Wash bay 1', washBay1_data);
printServiceTimeTable('Wash bay 2', washBay2_data);
printServiceTimeTable('Wash bay 3', washBay3_data);

% Initialize interarrival times based on probabilities
car_Interval = zeros(1, Number_Of_Cars);

% Initialize wash bay-specific car arrays
car_WashBay1 = [];
car_WashBay2 = [];
car_WashBay3 = [];

% Generating interarrival times and assigning cars to wash bays
for count = 1:Number_Of_Cars
    carRandInterval = generateRandomInt(1, 100);  % Generate integer between 1 and 100
    if count == 1
        car_Interval(count) = 0;
    else
        car_Interval(count) = getTimeFromRange(carRandInterval, interArrival_Data);
    end
    
    % Assign cars to the corresponding wash bay
    switch mod(count, 3)
        case 1
            randValue = generateRandomInt(1, 100);
            car_WashBay1 = [car_WashBay1; count, getServiceTime(randValue, washBay1_data), car_Interval(count)];
        case 2
            randValue = generateRandomInt(1, 100);
            car_WashBay2 = [car_WashBay2; count, getServiceTime(randValue, washBay2_data), car_Interval(count)];
        case 0
            randValue = generateRandomInt(1, 100);
            car_WashBay3 = [car_WashBay3; count, getServiceTime(randValue, washBay3_data), car_Interval(count)];
    end
end

% Display car information table for each wash bay
fprintf('****************WashBay 1****************:\n');
displayTable(car_WashBay1);

fprintf('****************WashBay 2****************:\n');
displayTable(car_WashBay2);

fprintf('****************WashBay 3****************:\n');
displayTable(car_WashBay3);

% Simulate car arrivals and services
simulateCars(Number_Of_Cars, car_Interval, {car_WashBay1, car_WashBay2, car_WashBay3});

% Evaluate and display results
evaluateResults(car_Interval, {car_WashBay1, car_WashBay2, car_WashBay3});
