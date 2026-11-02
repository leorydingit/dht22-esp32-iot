CREATE EXTENSION IF NOT EXISTS timescaledb;

CREATE TABLE readings (
  time        TIMESTAMPTZ      NOT NULL DEFAULT now(),
  device      TEXT             NOT NULL,
  temperature DOUBLE PRECISION,
  humidity    DOUBLE PRECISION
);

-- Turn it into a hypertable (auto-partitioned by time)
SELECT create_hypertable('readings', by_range('time'));
CREATE INDEX ON readings (device, time DESC);

-- Optional: hourly averages kept up to date automatically
CREATE MATERIALIZED VIEW readings_hourly
WITH (timescaledb.continuous) AS
SELECT time_bucket('1 hour', time) AS bucket,
       device,
       avg(temperature) AS avg_temp,
       min(temperature) AS min_temp,
       max(temperature) AS max_temp,
       avg(humidity)    AS avg_humidity
FROM readings
GROUP BY bucket, device;

SELECT add_continuous_aggregate_policy('readings_hourly',
  start_offset      => INTERVAL '3 hours',
  end_offset        => INTERVAL '1 hour',
  schedule_interval => INTERVAL '1 hour');

-- Optional: delete raw readings older than 1 year
SELECT add_retention_policy('readings', INTERVAL '1 year');