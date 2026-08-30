clear;
clc;

fprintf('\n************************************************************\n');
fprintf('*           Radiant Ride Car Wash Center Simulator         *\n');
fprintf('************************************************************\n');

car = {...
'                          ______  ';...
'                        //  ||\ \ ';...
'                    ___//___||_\ \___';...
'                   |    _        _   |';...
'                   |___/ \______/ \__|';...
'-----------------------\_/------\_/-------------------------';...
'____________________________________________________________'};

% Display the car
for i = 1:numel(car)
    fprintf('%s\n', car{i});
end

fprintf('\n');

% Select the random number generator type
rng_type = selectRNGType();

% Input the seed value(s)
seed1 = input('Enter the first seed value: ');
if rng_type == 2
    seed2 = input('Enter the second seed value: ');
else
    seed2 = []; % LCG does not need a second seed
end

% Select the rule for assigning cars to wash bays
fprintf('Choose rule for waiting line:\n');
fprintf('1 - Cars go to wash bays in sequential manner (i.e., car 1 to wash bay 1, car 2 to wash bay 2, and so on)\n');
fprintf('2 - Cars go to idle wash bay, and if all wash bays are idle, go to wash bay 1\n');
rule_choice = input('Choice: ');

% Input the number of cars
Number_Of_Cars = input('Enter the number of cars: ');

% Generate tables for service times, inter-arrival times, and service types
[washBay1_data, washBay2_data, washBay3_data] = generateServiceTimeTables(rng_type, seed1, seed2);
interArrival_Data = generateInterArrivalTimeTable(rng_type, seed1, seed2);
serviceTypes_Data = generateServiceTypesTable(rng_type, seed1, seed2);

% Print the service time tables
fprintf('\n========================================================\n');
fprintf('================ CAR WASH SERVICE TIMES ================\n');
fprintf('========================================================\n\n');

printServiceTimeTable('***************** W A S H   B A Y   1 ******************', washBay1_data);
printServiceTimeTable('***************** W A S H   B A Y   2 ******************', washBay2_data);
printServiceTimeTable('***************** W A S H   B A Y   3 ******************', washBay3_data);

% Print the inter-arrival time table
fprintf('\n<----<<----< I N T E R - A R R I V A L   T I M E >---->>---->\n');
printInterArrivalTimeTable(interArrival_Data);

% Print the service types table
fprintf('\n<<------<<------< S E R V I C E   T Y P E S >------>>------>>\n');
printServiceTypesTable(serviceTypes_Data);

% Simulate car arrivals and services
fprintf('\n:::::::::::::::::::::::::::::::::: A R R I V A L S  &  S E R V I C E S :::::::::::::::::::::::::::::::\n\n');
simulateCars(Number_Of_Cars, interArrival_Data, washBay1_data, washBay2_data, washBay3_data, serviceTypes_Data, rule_choice);
