function time = getTimeFromRange(randValue, data)
    for i = 1:size(data, 1)
        range = [data(i, 4), data(i, 5)];
        if randValue >= range(1) && randValue <= range(2)
            time = data(i, 1);
            return;
        end
    end
end
