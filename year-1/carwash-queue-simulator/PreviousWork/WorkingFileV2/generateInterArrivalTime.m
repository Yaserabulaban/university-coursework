function data = generateInterArrivalTime(rng_type)
    fprintf('\n-------- I N T E R A R R I V A L   T I M E ---------\n');
    num_rows = 5; % Assuming 5 rows for simplicity
    data = zeros(num_rows, 2);
    for i = 1:num_rows
        data(i, 1) = randi([1, 5]); % Generate integer between 1 and 5
        data(i, 2) = rand() / num_rows; % Example probability
    end
    displayInterarrivalTime(data);
end
