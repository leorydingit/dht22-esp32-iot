import os
from fastapi import FastAPI
from pydantic import BaseModel, Field
from psycopg_pool import ConnectionPool

DSN = os.getenv("DATABASE_URL",
                "postgresql://${POSTGRES_USER}:${POSTGRES_PASSWORD}@localhost:5432/${POSTGRES_DB}")
pool = ConnectionPool(DSN, min_size=1, max_size=5, open=True)
app = FastAPI()

class Reading(BaseModel):
    device: str = Field(max_length=64)
    temperature: float = Field(ge=-40, le=80)   # DHT22 range
    humidity: float = Field(ge=0, le=100)

@app.post("/readings", status_code=201)
def add_reading(r: Reading):
    with pool.connection() as conn:
        conn.execute(
            "INSERT INTO readings (device, temperature, humidity) "
            "VALUES (%s, %s, %s)",
            (r.device, r.temperature, r.humidity),
        )
    return {"ok": True}

@app.get("/readings/latest")
def latest():
    with pool.connection() as conn:
        rows = conn.execute(
            "SELECT DISTINCT ON (device) device, time, temperature, humidity "
            "FROM readings ORDER BY device, time DESC"
        ).fetchall()
    return [
        {"device": d, "time": t.isoformat(), "temperature": te, "humidity": h}
        for d, t, te, h in rows
    ]