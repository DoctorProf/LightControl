package com.example.mobile.retrofit

import com.example.mobile.retrofit.dto.Mode
import com.example.mobile.retrofit.dto.Response
import com.example.mobile.retrofit.dto.Settings
import retrofit2.Call
import retrofit2.http.Body
import retrofit2.http.DELETE
import retrofit2.http.GET
import retrofit2.http.POST
import retrofit2.http.Query
import retrofit2.http.QueryMap

interface ApiService {
    @GET("/getSettings")
    suspend fun getSettings(): Settings

    @GET("/setSettings")
    suspend fun setSettings(@QueryMap params: Map<String, Int>): Response

    @GET("/modes")
    suspend fun getModes(): List<Mode>

    @GET("/mode")
    suspend fun setModeParameter(@QueryMap params: Map<String, String>): Response

    @POST("/mode")
    suspend fun addMode(@Body mode: Mode): Response

    @DELETE("/mode")
    suspend fun deleteMode(): Response
}