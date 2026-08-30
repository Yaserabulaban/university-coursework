function [washBay1_data, washBay2_data, washBay3_data] = generateServiceTimeTables(rng_type)
    washBay1_data = generateServiceTimeTable('Wash Bay 1', rng_type);
    washBay2_data = generateServiceTimeTable('Wash Bay 2', rng_type);
    washBay3_data = generateServiceTimeTable('Wash Bay 3', rng_type);
end
