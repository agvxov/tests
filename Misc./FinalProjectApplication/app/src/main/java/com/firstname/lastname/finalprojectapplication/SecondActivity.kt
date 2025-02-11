package com.firstname.lastname.finalprojectapplication

import android.content.Intent
import android.os.Bundle
import android.view.KeyEvent
import android.view.View
import androidx.activity.enableEdgeToEdge
import androidx.appcompat.app.AppCompatActivity
import androidx.core.view.ViewCompat
import androidx.core.view.WindowInsetsCompat
import android.widget.Button
import android.widget.EditText


class SecondActivity : AppCompatActivity() {
    private val appenderTextView : EditText = findViewById(R.id.AppenderEditText)
    private val gotoButton : Button = findViewById(R.id.button3)
    private val viewItems = arrayListOf(
        "Dashing through the snow",
        "In a one-horse open sleigh",
        "O'er the fields we go",
        "Laughing all the way.",
        "The bells on bob-tail ring",
        "They make our spirits bright",
        "What fun it is to ride and sing",
        "A sleighing song tonight.",
        "Jingle bells, jingle bells",
        "Jingle all the way,",
        "Oh, what fun it is to ride",
        "In a one-horse open sleigh!",
        "Jingle bells, jingle bells",
        "Jingle all the way,",
        "Oh, what fun it is to ride",
        "In a one-horse open sleigh!"
    )


    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        enableEdgeToEdge()
        setContentView(R.layout.activity_second)
        ViewCompat.setOnApplyWindowInsetsListener(findViewById(R.id.main)) { v, insets ->
            val systemBars = insets.getInsets(WindowInsetsCompat.Type.systemBars())
            v.setPadding(systemBars.left, systemBars.top, systemBars.right, systemBars.bottom)
            insets
        }

        val adapter = MyAdapter(viewItems)


        appenderTextView.setOnKeyListener(View.OnKeyListener {
                view, keyCode, event ->
            if (keyCode == KeyEvent.KEYCODE_ENTER
                && event.action == KeyEvent.ACTION_UP){
                viewItems.add(appenderTextView.text.toString())
                adapter.notifyDataSetChanged()
            }
            false
        })

        gotoButton.setOnClickListener(View.OnClickListener {
            var intent = Intent(this, SensorActivity::class.java)
            startActivity(intent)
        })
    }
}