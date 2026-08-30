function displayTable(car_WashBay)
    % Function to display the car wash bay data in a formatted table
    % Inputs:
    %   car_WashBay - cell array containing car data [Car ID, Service Time, Arrival Time, Service Type]

    % Validate input
    %if size(car_WashBay, 2) ~= 4
     %   disp('Invalid input data structure:');
      %  disp(car_WashBay); % Display the current car_WashBay to debug the issue
       % error('Input matrix must have 4 columns: [Car ID, Service Time, Arrival Time, Service Type]');
    %end

    % Print table header
    %fprintf('%-10s%-15s%-15s%-20s\n', 'Car ID', 'Service Time', 'Arrival Time', 'Service Type');

    % Print each row of the table
    %for i = 1:size(car_WashBay, 1)
     %   fprintf('%-10d%-15d%-15d%-20s\n', car_WashBay{i, 1}, car_WashBay{i, 2}, car_WashBay{i, 3}, car_WashBay{i, 4});
    %end
%end
