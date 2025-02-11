package com.firstname.lastname.finalprojectapplication

import android.content.Intent
import android.net.Uri
import android.os.Bundle
import android.view.View
import android.widget.Button
import android.widget.EditText
import androidx.activity.enableEdgeToEdge
import androidx.appcompat.app.AppCompatActivity
import androidx.core.view.ViewCompat
import androidx.core.view.WindowInsetsCompat

class MainActivity : AppCompatActivity() {
    private val text1 : EditText = findViewById(R.id.editTextText)
    private val text2 : EditText = findViewById(R.id.editTextText)
    private val callButton : Button = findViewById(R.id.button2)
    private val gotoButton : Button = findViewById(R.id.button)

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        enableEdgeToEdge()
        setContentView(R.layout.activity_main)
        ViewCompat.setOnApplyWindowInsetsListener(findViewById(R.id.main)) { v, insets ->
            val systemBars = insets.getInsets(WindowInsetsCompat.Type.systemBars())
            v.setPadding(systemBars.left, systemBars.top, systemBars.right, systemBars.bottom)
            insets
        }

        callButton.setOnClickListener(View.OnClickListener {
            var intent = Intent(Intent.ACTION_CALL).apply {
                text2.setText(text1.text.toString())

                data = Uri.parse("tel:+112233445566")
                startActivity(intent)
            }
        })

        gotoButton.setOnClickListener(View.OnClickListener {
            var intent = Intent(this, SecondActivity::class.java)
            startActivity(intent)
        })
    }
}