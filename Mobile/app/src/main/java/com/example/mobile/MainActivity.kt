package com.example.mobile

import android.os.Bundle
import android.view.View
import android.widget.AdapterView
import android.widget.SeekBar
import android.widget.SeekBar.OnSeekBarChangeListener
import androidx.appcompat.app.AppCompatActivity
import com.example.mobile.databinding.ActivityMainBinding
import com.example.mobile.retrofit.ApiService
import com.example.mobile.retrofit.dto.Mode
import kotlinx.coroutines.CoroutineScope
import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.launch
import retrofit2.Retrofit
import retrofit2.converter.gson.GsonConverterFactory

class MainActivity : AppCompatActivity() {
    private lateinit var binding: ActivityMainBinding

    override fun onCreate(savedInstanceState: Bundle?) {
            super.onCreate(savedInstanceState)
            binding = ActivityMainBinding.inflate(layoutInflater)
            setContentView(binding.root)

            val retrofit = Retrofit.Builder()
                .baseUrl("http://192.168.0.104:8080")
                .addConverterFactory(GsonConverterFactory.create())
                .build()

            val apiService = retrofit.create(ApiService::class.java)
            with(binding) {
                brightness.setOnSeekBarChangeListener(object : OnSeekBarChangeListener {
                    override fun onProgressChanged(seekBar: SeekBar, progress: Int, fromUser: Boolean) {
                        brightnessValue.text = progress.toString()
                        CoroutineScope(Dispatchers.IO).launch {
                            apiService.setSettings(mapOf("brightness" to progress))
                        }
                    }
                    override fun onStartTrackingTouch(seekBar: SeekBar) { }
                    override fun onStopTrackingTouch(seekBar: SeekBar) { }
                })
                modes.onItemSelectedListener = object : AdapterView.OnItemSelectedListener {
                    override fun onItemSelected(parent: AdapterView<*>, view: View?, position: Int, id: Long) {
                        val selectedMode = parent.getItemAtPosition(position) as Mode
                        CoroutineScope(Dispatchers.IO).launch {
                            apiService.setSettings(mapOf("mode_id" to selectedMode.id))
                        }
                    }
                    override fun onNothingSelected(parent: AdapterView<*>) { }
                }
                state.setOnCheckedChangeListener { buttonView, isChecked ->
                    CoroutineScope(Dispatchers.IO).launch {
                        val stateInt = if (isChecked) 1 else 0
                        apiService.setSettings(mapOf("state" to stateInt))
                    }
                }
                delete.setOnClickListener {
                    CoroutineScope(Dispatchers.IO).launch {
                        apiService.deleteMode()
                    }
                }
            }
            CoroutineScope(Dispatchers.IO).launch {
                val settings = apiService.getSettings()
                runOnUiThread {
                    binding.brightness.progress = settings.brightness
                    binding.brightnessValue.text = settings.brightness.toString()
                    binding.state.isChecked = settings.state != 0
                }
            }
            CoroutineScope(Dispatchers.IO).launch {
                val modes = apiService.getModes()
                runOnUiThread {
                    val adapter = ModeSpinnerAdapter(this@MainActivity, modes);
                    binding.modes.adapter = adapter
                }
            }
        }
    }