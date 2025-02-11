package com.firstname.lastname.finalprojectapplication

import android.hardware.Sensor
import android.hardware.SensorEvent
import android.hardware.SensorEventListener
import android.hardware.SensorManager
import android.os.Bundle
import android.widget.EditText
import android.widget.TextView
import androidx.activity.enableEdgeToEdge
import androidx.appcompat.app.AppCompatActivity
import androidx.core.view.ViewCompat
import androidx.core.view.WindowInsetsCompat

class SensorActivity : AppCompatActivity(), SensorEventListener {
    private lateinit var sensorManager : SensorManager
    private var mySensor : Sensor? = null
    private val textViewX : TextView = findViewById(R.id.textViewX)
    private val textViewY : TextView = findViewById(R.id.textViewY)
    private val textViewZ : TextView = findViewById(R.id.textViewZ)

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        enableEdgeToEdge()
        setContentView(R.layout.activity_sensor)
        ViewCompat.setOnApplyWindowInsetsListener(findViewById(R.id.main)) { v, insets ->
            val systemBars = insets.getInsets(WindowInsetsCompat.Type.systemBars())
            v.setPadding(systemBars.left, systemBars.top, systemBars.right, systemBars.bottom)
            insets
        }

        sensorManager = getSystemService(SENSOR_SERVICE) as SensorManager
        mySensor = sensorManager.getDefaultSensor(Sensor.TYPE_ACCELEROMETER)
    }

    override fun onSensorChanged(event: SensorEvent?) {
        event?.also {
            val x = event.values.get(0)
            val y = event.values.get(1)
            val z = event.values.get(2)
            textViewX.text = x.toString()
            textViewY.text = y.toString()
            textViewZ.text = z.toString()
        }
    }

    override fun onAccuracyChanged(sensor: Sensor?, accuracy: Int) { /* ; */ }

    override fun onResume() {
        super.onResume()
        mySensor?.also {
            sensorManager.registerListener(this, mySensor, SensorManager.SENSOR_DELAY_NORMAL)
        }
    }

    override fun onPause() {
        super.onPause()
        mySensor?.also {
            sensorManager.unregisterListener(this)
        }
    }
}